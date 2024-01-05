#version 330 core

layout (location = 0) in vec3 pos;

/// <summary>
/// モデル用定数バッファ。
/// </summary>
layout (std140) uniform ModelUB
{
	mat4 mModel;
	mat4 mView;
	mat4 mProj;
} modelUB;

void main()
{
	vec4 position;
	position = modelUB.mModel * vec4(pos, 1.0f);
	position = modelUB.mView * position;
	position = modelUB.mProj * position;
	gl_Position = position;
}