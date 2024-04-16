#version 330 core

/// <summary>
/// ピクセルシェーダーへの入力。
/// </summary>
in SPSIn
{
	vec4 pos;
	vec3 color;
} psIn;

out vec4 FragColor;

void main()
{
	FragColor.rgb = psIn.color;
    FragColor.a = 1.0f;
}