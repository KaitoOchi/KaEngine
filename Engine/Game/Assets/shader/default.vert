#version 330 core

/// <summary>
/// 頂点シェーダーへの入力。
/// </summary>
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uv;

/// <summary>
/// ピクセルシェーダーへの出力。
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
/// モデル用定数バッファ。
/// </summary>
layout (std140) uniform ModelUB
{
	mat4 mModel;
	mat4 mView;
	mat4 mProj;
} modelUB;

/// <summary>
/// VertexShaderのエントリー関数。
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