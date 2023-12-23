////////////////////////////////////////////////
// PBR���C�e�B���O�B
////////////////////////////////////////////////

/// <summary>
/// �t���l�����˂��l�������g�U���˂��v�Z�B
/// </summary>
/// <param name="normal">�@��</param>
/// <param name="dir">�����Ɍ������x�N�g���B���̕����Ƌt�����̃x�N�g��</param>
/// <param name="toEye">�����Ɍ������x�N�g��</param>
float CalcDiffuseFromFresnel(vec3 dir, vec3 toEye, vec3 normal, float smooth)
{
	//�����Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�B
    vec3 H = normalize(dir + toEye);
    
	//�e�������߂�B
	float roughness = 1.0f - smooth;
	float energyBias = lerp(0.0f, 0.5f, roughness);
	float energyFactor = lerp(1.0f, 1.0f / 1.51f, roughness);

	//�����Ɍ������x�N�g���ƃn�[�t�x�N�g�����ǂꂾ�����Ă��邩����ςŋ��߂�B
	float dotLH = saturate(dot(dir, H));

	//�������s�ɓ��˂����Ƃ��̊g�U���˗ʂ����߂�B
	float Fd90 = energyBias + 2.0f * dotLH * dotLH * roughness;

	//�@���ƌ����Ɍ������x�N�g���𗘗p���Ċg�U���˗������߂�B
	float dotNL = saturate(dot(normal, dir));
	float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

	//�@���Ǝ��_�Ɍ������ׂ����𗘗p���Ċg�U���˗������߂�B
	float dotNV = saturate(dot(normal, toEye));
	float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));

	//�@���ƌ����ւ̕����Ɉˑ�����g�U���˗���
	//�@���Ǝ��_�x�N�g���Ɉˑ�����g�U���˗�����Z���āA�ŏI�I�Ȋg�U���˗������߂�B
	return (FL * FV * energyFactor);
}

/// <summary>
/// �x�b�N�}�����z���v�Z�B
/// </summary>
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f-t2)/ t2);
    return D;
}

/// <summary>
/// �t���l�����v�Z�BSchlick�ߎ����g�p�B
/// </summary>
float SpcFresnel(float f0, float u)
{
    return f0 + (1-f0) * pow(1-u, 5);
}

/// <summary>
/// Cook-Torrance���f���̋��ʔ��˂��v�Z�B
/// </summary>
/// <param name="dir">�����Ɍ������x�N�g��</param>
/// <param name="toEye">���_�Ɍ������x�N�g��</param>
/// <param name="normal">�@���x�N�g��</param>
/// <param name="smooth">���炩��</param>
float CookTorranceSpecular(
    vec3 dir,
    vec3 toEye,
    vec3 normal,
    float smooth
)
{
    float microfacet = min(0.5f, 1.0f - smooth);

    // �����x�𐂒����˂̎��̃t���l�����˗��Ƃ��Ĉ����B
    // �����x�������قǃt���l�����˂͑傫���Ȃ�B
    float f0 = 0.5f;

    // ���C�g�Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�B
    vec3 H = normalize(dir + toEye);

    // �e��x�N�g�����ǂꂭ�炢���Ă��邩����ς𗘗p���ċ��߂�B
    float NdotH = max(0.001f, min(dot(normal, H), 1.0f));
    float VdotH = max(0.001f, min(dot(toEye, H),  1.0f));
    float NdotL = max(0.001f, min(dot(normal, dir), 1.0f));
    float NdotV = max(0.001f, min(dot(normal, toEye), 1.0f));

    // D�����x�b�N�}�����z��p���Čv�Z����B
    float D = Beckmann(microfacet, NdotH);

    // F����Schlick�ߎ���p���Čv�Z����B
    float F = SpcFresnel(f0, VdotH);

    // G�������߂�B
    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

    // m�������߂�B
    float m = PI * NdotV * NdotH;

    // �����܂ŋ��߂��A�l�𗘗p���āACook-Torrance���f���̋��ʔ��˂����߂�
    return saturate(F * D * G / m);
}