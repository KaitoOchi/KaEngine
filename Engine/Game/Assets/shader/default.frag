#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

/// <summary>
/// ピクセルシェーダーへの入力。
/// </summary>
in SPSIn
{
	vec3 color;
	vec2 texCoord;
	vec3 Normal;
	vec3 crntPos;	
} psIn;

// Gets the Texture Unit from the main function
uniform sampler2D g_albedoMap;
uniform sampler2D g_normalMap;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

vec4 CalcPointLight()
{
	vec4 lig;

	// diffuse lighting
	vec3 normal = normalize(psIn.Normal);
	vec3 lightDirection = normalize(lightPos - psIn.crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(cameraPos - psIn.crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	lig += diffuse * specular;
	lig *= lightColor;

	return lig;
}

/// <summary>
/// FragmentShaderのエントリー関数。
/// </summary>
void main()
{
	// ambient lighting
	float ambient = 0.5f;

	vec4 lig = CalcPointLight();

	vec4 albedoColor = texture(g_normalMap, psIn.texCoord);

	lig += albedoColor * ambient;

	FragColor = lig;
}
