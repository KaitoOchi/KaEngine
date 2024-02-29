#version 330 core

/// <summary>
/// �s�N�Z���V�F�[�_�[�ւ̓��́B
/// </summary>
in SPSIn
{
	vec4 pos;
	vec2 uv;
} psIn;

/// <summary>
/// ���f���p�萔�o�b�t�@�B
/// </summary>
layout (std140) uniform SpriteUB
{
	mat4 mvp;
    vec4 mulColor;

} spriteUB;

out vec4 FragColor;
uniform sampler2D colorTexture;

/// <summary>
/// �Z�s�A���ɂ���B
/// </summary>
vec4 CalcSepiaTone(vec4 albedo)
{
    //�������Ƃɏd�݂𕪂���
    float Y = 0.299f * albedo.r + 0.587f * albedo.g + 0.114f * albedo.b;

    //��Z���ăZ�s�A���ɉ��H����
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