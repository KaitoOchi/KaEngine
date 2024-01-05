#version 330 core

#include PBRLighting.h
#include PBRLighting_struct.h

// Outputs colors in RGBA
out vec4 FragColor;

/// <summary>
/// ピクセルシェーダーへの入力。
/// </summary>
in SPSIn
{
	vec4 pos;
	vec3 normal;
	vec3 color;
	vec2 uv;
	vec3 worldPos;
} psIn;

/// <summary>
/// ライト用定数バッファ。
/// </summary>
layout (std140) uniform LightUB
{
	DirectionLightUB dirLig;
	PointLightUB ptLig;
	vec3 eyePos;
} lightUB;

// Gets the Texture Unit from the main function
uniform sampler2D g_albedoMap;
uniform sampler2D g_normalMap;
uniform sampler2D g_metallicSmoothMap;

/// <summary>
/// ポイントライトを計算。
/// </summary>
/// <param name="toEye">視点の方向</param>
/// <param name="specularColor">スペキュラカラー</param>
/// <param name="metallic">金属度</param>
/// <param name="smooth">滑らかさ</param>
vec3 CalcPointLight(
	vec3 toEye,
	vec3 normal,
	vec3 specular,
	float metallic,
	float smooths
) {
	//サーフェイスに入射するポイントライトの正規化ベクトルを計算する。
	vec3 ligDir = normalize(psIn.worldPos - lightUB.ptLig.ptPosition);

	//ライトの計算。
	vec3 lig = CalcLighting(
		ligDir,
		lightUB.ptLig.ptColor,
		toEye,
		normal,
		specular,
		metallic,
		smooths
	);

	//ポイントライトとの距離を計算する。
	float distance = length(psIn.worldPos - lightUB.ptLig.ptPosition);
	//影響率は距離に比例して小さくなっていく。
	float affect = 1.0f - min(1.0f, distance / lightUB.ptLig.ptRange);
	//影響を指数関数的にする。
	lig *= pow(affect, 5.0f);

	return lig;
}

/// <summary>
/// FragmentShaderのエントリー関数。
/// </summary>
void main()
{
	//アルベドカラー。
	vec4 albedoColor = texture(g_albedoMap, psIn.uv);
	//法線。
	vec3 normal = psIn.normal;
	//メタリックスムース。
	float metallic = 0.0f;
	float smooths = 0.0f;
	//スペキュラカラー。
	vec3 specular = albedoColor.xyz;
	
	//視点の方向。
	vec3 toEye = normalize(lightUB.eyePos - psIn.worldPos);

	//ディレクションライトを計算。
	vec3 lig = CalcLighting(
		lightUB.dirLig.dirDirection,
		lightUB.dirLig.dirColor,
		toEye,
		normal,
		specular,
		metallic,
		smooths
	);

	//ポイントライトを計算。
	lig += CalcPointLight(
		toEye,
		normal,
		specular,
		metallic,
		smooths
	);

	lig += albedoColor.xyz * lightUB.dirLig.ambient;

	FragColor.xyz = lig;
	FragColor.w = 1.0f;
}
