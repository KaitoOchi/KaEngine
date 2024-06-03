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
	void Render(RenderContext& rc);

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
	CapsuleCollider m_capsuleCollider;			//�J�v�Z���R���C�_�[�B
	Rigidbody		m_rigidbody;				//���́B
	Vector2			m_rotSpeed;					//��]�p�x�B
	Vector3			m_position;					//���W�B
	Vector3			m_target;					//�����_�B
	float			m_sensitivity = 5.0f;		//�J�������x�B
};
