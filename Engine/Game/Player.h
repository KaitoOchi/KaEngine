#pragma once

/// <summary>
/// �v���C���[�B
/// </summary>
class Player : public GameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render();

	const Vector2& Get() const
	{
		return m_rotSpeed;
	}

private:
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();
	/// <summary>
	/// ��]�����B
	/// </summary>
	void Rotation();
	/// <summary>
	/// �J�[�\���̃��b�N�����B
	/// </summary>
	void CursorLock();

private:
	Vector2			m_rotSpeed;					//��]�p�x�B
	Vector3			m_position;					//���W�B
	Vector3			m_target;					//�����_�B
	float			m_sensitivity = 0.05f;		//�J�������x�B
};

