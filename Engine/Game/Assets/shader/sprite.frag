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

void main()
{
	FragColor = texture(colorTexture, psIn.uv) * spriteUB.mulColor;
}