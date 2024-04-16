#version 330 core

/// <summary>
/// 頂点シェーダーへの入力。
/// </summary>
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

/// <summary>
/// ピクセルシェーダーへの出力。
/// </summary>
out SPSIn
{
	vec4 pos;
	vec3 color;
} psIn;


/// <summary>
/// 行列用定数バッファ。
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