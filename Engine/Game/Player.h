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
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();

	/// <summary>
	/// ��]�����B
	/// </summary>
	void Rotation();

private:
	Vector2			m_rotSpeed;					//��]�p�x�B
	Vector3			m_position;					//���W�B
	Vector3			m_target;					//�����_�B
	float			m_sensitivity = 0.01f;		//�J�������x�B
};
