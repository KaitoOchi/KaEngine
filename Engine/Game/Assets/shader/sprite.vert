#version 330 core

/// <summary>
/// 頂点シェーダーへの入力。
/// </summary>
layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 uv;

/// <summary>
/// ピクセルシェーダーへの出力。
/// </summary>
out SPSIn
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

void main()
{
    psIn.pos = spriteUB.mvp * pos;

    psIn.uv = uv;

	gl_Position = psIn.pos;
}