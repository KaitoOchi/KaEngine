#version 330 core

/// <summary>
/// ���_�V�F�[�_�[�ւ̓��́B
/// </summary>
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uv;

/// <summary>
/// �s�N�Z���V�F�[�_�[�ւ̏o�́B
/// </summary>
out SPSIn
{
	vec4 pos;
	vec3 normal;
	vec3 color;
	vec2 uv;
	vec3 worldPos;
} psIn;

/// <summary>
/// ���f���p�萔�o�b�t�@�B
/// </summary>
layout (std140) uniform ModelUB
{
	mat4 mModel;
	mat4 mView;
	mat4 mProj;
} modelUB;

/// <summary>
/// VertexShader�̃G���g���[�֐��B
/// </summary>
void main()
{
	psIn.pos = modelUB.mModel * vec4(pos, 1.0f);
	psIn.worldPos = psIn.pos.xyz;
	psIn.pos = modelUB.mView * psIn.pos;
	psIn.pos = modelUB.mProj * psIn.pos;
	
	psIn.normal = normal;
	psIn.color = color;
	psIn.uv = uv;

	gl_Position = psIn.pos;
}