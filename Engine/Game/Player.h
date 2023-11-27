#pragma once

/// <summary>
/// プレイヤー。
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
	float		m_cameraSpeed = 0.0001f;		//カメラ速度。
	float		m_sensitivity = 0.01f;		//カメラ感度。
};

