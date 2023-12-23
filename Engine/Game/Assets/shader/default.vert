#version 330 core

/// <summary>
/// ���_�V�F�[�_�[�ւ̓��́B
/// </summary>
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

/// <summary>
/// �s�N�Z���V�F�[�_�[�ւ̏o�́B
/// </summary>
out SPSIn
{
	vec3 color;
	vec2 texCoord;

	vec3 Normal;
	vec3 crntPos;	
} psIn;

layout (std140) uniform ModelUB
{
	mat4 mView;
} uniformBuffer;

// Imports the camera matrix from the main function
uniform mat4 cameraMatrix;
uniform mat4 model;

/// <summary>
/// VertexShader�̃G���g���[�֐��B
/// </summary>
void main()
{
	psIn.crntPos = vec3(model * vec4(aPos, 1.0f));
	psIn.color = aColor;
	psIn.texCoord = aTex;
	psIn.Normal = aNormal;

	gl_Position = cameraMatrix * vec4(psIn.crntPos, 1.0);
}