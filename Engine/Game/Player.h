#pragma once

/// <summary>
/// プレイヤー。
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
	/// 移動処理。
	/// </summary>
	void Move();
	/// <summary>
	/// 回転処理。
	/// </summary>
	void Rotation();
	/// <summary>
	/// カーソルのロック処理。
	/// </summary>
	void CursorLock();

private:
	Vector2			m_rotSpeed;					//回転角度。
	Vector3			m_position;					//座標。
	Vector3			m_target;					//注視点。
	float			m_sensitivity = 0.05f;		//カメラ感度。
};

