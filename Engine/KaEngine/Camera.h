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
		/// <param name="width"></param>
		/// <param name="height"></param>
		Camera(const float width, const float height, Shader* shader);

		~Camera();

		void Update();

		void Input();

	public:
		/// <summary>
		/// 近平面の設定。
		/// </summary>
		/// <param name=""></param>
		void SetNear(const float near)
		{
			m_near = near;
		}

		/// <summary>
		/// 遠平面の設定。
		/// </summary>
		/// <param name=""></param>
		void SetFar(const float far)
		{
			m_far = far;
		}

		/// <summary>
		/// 視野角を設定。
		/// </summary>
		/// <param name="fov"></param>
		void SetFOV(const float fov)
		{
			m_fov = fov;
		}

	private:
		Shader*		m_shader = nullptr;		//シェーダー。
		Vector3		m_position;				//座標。
		Vector3		m_forward;				//前方向。
		Vector3		m_up;					//上。
		float		m_width = 0.0f;			//横幅。
		float		m_height = 0.0f;		//高さ。
		float		m_near = 0.1f;			//近平面。
		float		m_far = 1000.0f;		//遠平面。
		float		m_fov = 90.0f;			//視野角。

		float		m_cameraSpeed = 0.0f;	//カメラ速度。
		float		m_sensitivity = 0.0f;	//カメラ感度。
	};
}