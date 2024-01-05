////////////////////////////////////////////////
// PBRライティング。
////////////////////////////////////////////////
const float PI = 3.1415926;

/// <summary>
/// フレネル反射を考慮した拡散反射を計算。
/// </summary>
/// <param name="dir">高原に向かうベクトル。光の方向と逆向きのベクトル</param>
/// <param name="toEye">視線に向かうベクトル</param>
/// <param name="normal">法線</param>
float CalcDiffuseFromFresnel(
    vec3 dir,
    vec3 toEye,
    vec3 normal,
    float smooths
) {
	//光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める。
    vec3 H = normalize(dir + toEye);
    
	//粗さを求める。
	float roughness = 1.0f - smooths;
	float energyBias = mix(0.0f, 0.5f, roughness);
	float energyFactor = mix(1.0f, 1.0f / 1.51f, roughness);

	//光源に向かうベクトルとハーフベクトルがどれだけ似ているかを内積で求める。
	float dotLH = clamp(dot(dir, H), 0.0f, 1.0f);

	//光が平行に入射したときの拡散反射量を求める。
	float Fd90 = energyBias + 2.0f * dotLH * dotLH * roughness;

	//法線と光源に向かうベクトルを利用して拡散反射率を求める。
	float dotNL = clamp(dot(normal, dir), 0.0f, 1.0f);
	float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

	//法線と視点に向かうべう取るを利用して拡散反射率を求める。
	float dotNV = clamp(dot(normal, toEye), 0.0f, 1.0f);
	float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));

	//法線と光源への方向に依存する拡散反射率と
	//法線と視点ベクトルに依存する拡散反射率を乗算して、最終的な拡散反射率を求める。
	return (FL * FV * energyFactor);
}

/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
/// <param name="lightDirection">ライトの方向</param>
/// <param name="lightColor">ライトのカラー</param>
/// <param name="normal">法線</param>
vec3 CalcLambertDiffuse(
    vec3 lightDirection,
    vec3 lightColor,
    vec3 normal
) {
	//ピクセルの法線とライトの方向の内積を計算する
	float t = clamp(dot(normal, lightDirection), 0.0f, 1.0f);

	vec3 lambertDiffuse = (lightColor * t) / PI;

	return lambertDiffuse;
}

/// <summary>
/// ベックマン分布を計算。
/// </summary>
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f-t2)/ t2);
    return D;
}

/// <summary>
/// フレネルを計算。Schlick近似を使用。
/// </summary>
float SpcFresnel(float f0, float u)
{
    return f0 + (1-f0) * pow(1-u, 5);
}

/// <summary>
/// Cook-Torranceモデルの鏡面反射を計算。
/// </summary>
/// <param name="dir">光源に向かうベクトル</param>
/// <param name="toEye">視点に向かうベクトル</param>
/// <param name="normal">法線ベクトル</param>
/// <param name="smooth">滑らかさ</param>
float CookTorranceSpecular(
    vec3 dir,
    vec3 toEye,
    vec3 normal,
    float smooths
)
{
    float microfacet = min(0.5f, 1.0f - smooths);

    // 金属度を垂直入射の時のフレネル反射率として扱う。
    // 金属度が高いほどフレネル反射は大きくなる。
    float f0 = 0.5f;

    // ライトに向かうベクトルと視線に向かうベクトルのハーフベクトルを求める。
    vec3 H = normalize(dir + toEye);

    // 各種ベクトルがどれくらい似ているかを内積を利用して求める。
    float NdotH = max(0.001f, min(dot(normal, H), 1.0f));
    float VdotH = max(0.001f, min(dot(toEye, H),  1.0f));
    float NdotL = max(0.001f, min(dot(normal, dir), 1.0f));
    float NdotV = max(0.001f, min(dot(normal, toEye), 1.0f));

    // D項をベックマン分布を用いて計算する。
    float D = Beckmann(microfacet, NdotH);

    // F項をSchlick近似を用いて計算する。
    float F = SpcFresnel(f0, VdotH);

    // G項を求める。
    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

    // m項を求める。
    float m = PI * NdotV * NdotH;

    // ここまで求めた、値を利用して、Cook-Torranceモデルの鏡面反射を求める
    return clamp(F * D * G / m, 0.0f, 1.0f);
}

/// <summary>
/// ライティングの計算。
/// </summary>
/// <param name="lightDirection">ライトの方向</param>
/// <param name="lightColor">ライトのカラー</param>
/// <param name="toEye">視点の方向</param>
/// <param name="normal">法線</param>
/// <param name="specularColor">スペキュラカラー</param>
/// <param name="metallic">金属度</param>
/// <param name="smooth">滑らかさ</param>
vec3 CalcLighting(
	vec3 lightDirection,
	vec3 lightColor,
	vec3 toEye,
    vec3 normal,
	vec3 specularColor,
	float metallic,
	float smooths
) {
	//フレネル反射を考慮した拡散反射を計算。
	float diffuseFromFresnel = CalcDiffuseFromFresnel(
		-lightDirection,
		toEye,
		normal,
		smooths
	);

	//正規化Lambert拡散反射を計算。
	vec3 lambertDiffuse = CalcLambertDiffuse(
		-lightDirection,
		lightColor,
		normal
	);

	//最終的な拡散反射光を計算する。
	vec3 diffuse = diffuseFromFresnel * lambertDiffuse;

	//Cook-Torranceモデルを利用した鏡面反射率を計算する。
	vec3 specular = CookTorranceSpecular(
		-lightDirection,
		toEye,
		normal,
		smooths
	) * lightColor;

	//金属度が高ければ、鏡面反射はスペキュラカラー、低ければライトの色。
	//スペキュラカラーの強さを鏡面反射率として扱う。
	specular *= mix(lightColor, specularColor, metallic);

	//滑らかさを使って、拡散反射光と鏡面反射光を合成する。
	//滑らかさが高ければ、拡散反射は弱くなる。
	return diffuse * (1.0f - smooths) + specular;
}
