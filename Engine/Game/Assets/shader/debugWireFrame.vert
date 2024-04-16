#version 330 core

/// <summary>
/// ���_�V�F�[�_�[�ւ̓��́B
/// </summary>
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

/// <summary>
/// �s�N�Z���V�F�[�_�[�ւ̏o�́B
/// </summary>
out SPSIn
{
	vec4 pos;
	vec3 color;
} psIn;


/// <summary>
/// �s��p�萔�o�b�t�@�B
/// </summary>
layout (std140) uniform MatrixUB
{
	mat4 mvp;
} matrix;

void main()
{
    psIn.pos = matrix.mvp * vec4(pos, 1.0f);

    psIn.color = color;

	gl_Position = psIn.pos;
}