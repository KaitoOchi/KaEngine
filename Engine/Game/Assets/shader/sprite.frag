#version 330 core

/// <summary>
/// ピクセルシェーダーへの入力。
/// </summary>
in SPSIn
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

out vec4 FragColor;
uniform sampler2D colorTexture;

void main()
{
	FragColor = texture(colorTexture, psIn.uv) * spriteUB.mulColor;
}