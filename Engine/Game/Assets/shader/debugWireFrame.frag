#version 330 core

/// <summary>
/// �s�N�Z���V�F�[�_�[�ւ̓��́B
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