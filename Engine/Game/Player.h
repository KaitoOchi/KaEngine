#pragma once

/// <summary>
/// �v���C���[�B
/// </summary>
class Player
{
public:
	Player();
	~Player();
	void Update();

private:
	Vector3		m_position;
	Quaternion m_rotation;
	float		m_cameraSpeed = 0.0001f;		//�J�������x�B
	float		m_sensitivity = 0.01f;		//�J�������x�B
};

