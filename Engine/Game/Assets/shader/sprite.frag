#version 330 core

/// <summary>
/// ピクセルシェーダーへの入力。
/// </summary>
in SPSIn
{
	vec4 pos;
	vec2 uv;
} psIn;

/// <summary>
/// モデル用定数バッファ。
/// </summary>
layout (std140) uniform SpriteUB
{
	mat4 mvp;
    vec4 mulColor;

} spriteUB;

out vec4 FragColor;
uniform sampler2D colorTexture;

/// <summary>
/// セピア調にする。
/// </summary>
vec4 CalcSepiaTone(vec4 albedo)
{
    //成分ごとに重みを分ける
    float Y = 0.299f * albedo.r + 0.587f * albedo.g + 0.114f * albedo.b;

    //乗算してセピア調に加工する
    vec3 sepiaColor;
    sepiaColor.r = Y * 1.1f;
    sepiaColor.g = Y * 0.9f;
    sepiaColor.b = Y * 0.6f;

    albedo.xyz = mix(albedo.xyz, sepiaColor, 1.0f);

    return albedo;
}

void main()
{
    vec4 albedoColor;
    albedoColor = texture(colorTexture, psIn.uv) * spriteUB.mulColor;

    //albedoColor = CalcSepiaTone(albedoColor);

	FragColor = albedoColor;
}