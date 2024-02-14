#version 330 core

/// <summary>
/// ���_�V�F�[�_�[�ւ̓��́B
/// </summary>
layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 uv;

/// <summary>
/// �s�N�Z���V�F�[�_�[�ւ̏o�́B
/// </summary>
out SPSIn
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

void main()
{
    psIn.pos = spriteUB.mvp * pos;

    psIn.uv = uv;

	gl_Position = psIn.pos;
}