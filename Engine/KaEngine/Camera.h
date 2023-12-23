#pragma once
#include "ShaderClass.h"

namespace nsKaEngine {

	/// <summary>
	/// カメラクラス。
	/// </summary>
	class Camera
	{
	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>
		Camera();
		~Camera();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="shader"></param>
		void Init();

		/// <summary>
		/// 更新処理。
		/// </summary>
		void Update();

	public:
		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// 座標を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// 注視点を設定。
		/// </summary>
		/// <param name="target"></param>
		void SetTarget(const Vector3& target)
		{
			m_target = target;
			Quaternion rot;
			rot.SetRotationFromVector(Vector3::AxisZ, m_target);
			m_rotation = rot;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// 注視点を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetTarget() const
		{
			return m_target;
		}

		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
			m_rotation.Apply(m_forward);
			m_forward.Normalize();
			m_target = m_forward * 50000.0f;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// 回転を取得。
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// 前方向を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetForward() const
		{
			return m_forward;
		}

		/// <summary>
		/// 上方向を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetUp() const
		{
			return m_up;
		}

		/// <summary>
		/// 右方向を取得。
		/// </summary>
		/// <returns></returns>
		const Vector3& GetRight() const
		{
			return m_right;
		}

		/// <summary>
		/// 近平面の設定。
		/// </summary>
		/// <param name=""></param>
		void SetNear(const float nearV)
		{
			m_near = nearV;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// 遠平面の設定。
		/// </summary>
		/// <param name=""></param>
		void SetFar(const float farV)
		{
			m_far = farV;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// 視野角を設定。
		/// </summary>
		/// <param name="fov"></param>
		void SetFOV(const float fov)
		{
			m_fov = fov;
			m_isNeedUpdate = true;
		}

		/// <summary>
		/// ビュープロジェクション行列を取得。
		/// </summary>
		/// <returns></returns>
		const Matrix& GetViewProjectionMatrix() const
		{
			return m_viewProjectionMatrix;
		}

	private:
		Vector3		m_position;						//座標。
		Vector3		m_target;						//注視点。
		Vector3		m_forward = Vector3::Forward;	//前方向。
		Vector3		m_up = Vector3::Up;				//上方向。
		Vector3		m_right = Vector3::AxisX;		//右方向。
		Quaternion	m_rotation;						//回転。
		Matrix		m_viewMatrix;					//ビュー行列。
		Matrix		m_viewMatrixInv;				//ビュー行列の逆行列。
		Matrix		m_projectionMatrix;				//透視変換行列。
		Matrix		m_projectionMatrixInv;			//透視変換行列の逆行列。
		Matrix		m_viewProjectionMatrix;			//ビュープロジェクション行列。
		Matrix		m_viewProjectionMatrixInv;		//ビュープロジェクション行列の逆行列。
		bool		m_isNeedUpdate = true;			//更新が必要かどうか。
		float		m_near = 0.1f;					//近平面。
		float		m_far = 1000.0f;				//遠平面。
		float		m_fov = 60.0f;					//視野角。
	};
}