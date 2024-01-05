#version 330 core

#include PBRLighting.h
#include PBRLighting_struct.h

// Outputs colors in RGBA
out vec4 FragColor;

/// <summary>
/// �s�N�Z���V�F�[�_�[�ւ̓��́B
/// </summary>
in SPSIn
{
	vec4 pos;
	vec3 normal;
	vec3 color;
	vec2 uv;
	vec3 worldPos;
} psIn;

/// <summary>
/// ���C�g�p�萔�o�b�t�@�B
/// </summary>
layout (std140) uniform LightUB
{
	DirectionLightUB dirLig;
	PointLightUB ptLig;
	vec3 eyePos;
} lightUB;

// Gets the Texture Unit from the main function
uniform sampler2D g_albedoMap;
uniform sampler2D g_normalMap;
uniform sampler2D g_metallicSmoothMap;

/// <summary>
/// �|�C���g���C�g���v�Z�B
/// </summary>
/// <param name="toEye">���_�̕���</param>
/// <param name="specularColor">�X�y�L�����J���[</param>
/// <param name="metallic">�����x</param>
/// <param name="smooth">���炩��</param>
vec3 CalcPointLight(
	vec3 toEye,
	vec3 normal,
	vec3 specular,
	float metallic,
	float smooths
) {
	//�T�[�t�F�C�X�ɓ��˂���|�C���g���C�g�̐��K���x�N�g�����v�Z����B
	vec3 ligDir = normalize(psIn.worldPos - lightUB.ptLig.ptPosition);

	//���C�g�̌v�Z�B
	vec3 lig = CalcLighting(
		ligDir,
		lightUB.ptLig.ptColor,
		toEye,
		normal,
		specular,
		metallic,
		smooths
	);

	//�|�C���g���C�g�Ƃ̋������v�Z����B
	float distance = length(psIn.worldPos - lightUB.ptLig.ptPosition);
	//�e�����͋����ɔ�Ⴕ�ď������Ȃ��Ă����B
	float affect = 1.0f - min(1.0f, distance / lightUB.ptLig.ptRange);
	//�e�����w���֐��I�ɂ���B
	lig *= pow(affect, 5.0f);

	return lig;
}

/// <summary>
/// FragmentShader�̃G���g���[�֐��B
/// </summary>
void main()
{
	//�A���x�h�J���[�B
	vec4 albedoColor = texture(g_albedoMap, psIn.uv);
	//�@���B
	vec3 normal = psIn.normal;
	//���^���b�N�X���[�X�B
	float metallic = 0.0f;
	float smooths = 0.0f;
	//�X�y�L�����J���[�B
	vec3 specular = albedoColor.xyz;
	
	//���_�̕����B
	vec3 toEye = normalize(lightUB.eyePos - psIn.worldPos);

	//�f�B���N�V�������C�g���v�Z�B
	vec3 lig = CalcLighting(
		lightUB.dirLig.dirDirection,
		lightUB.dirLig.dirColor,
		toEye,
		normal,
		specular,
		metallic,
		smooths
	);

	//�|�C���g���C�g���v�Z�B
	lig += CalcPointLight(
		toEye,
		normal,
		specular,
		metallic,
		smooths
	);

	lig += albedoColor.xyz * lightUB.dirLig.ambient;

	FragColor.xyz = lig;
	FragColor.w = 1.0f;
}
