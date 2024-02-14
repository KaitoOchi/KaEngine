#include "KaEnginePreCompile.h"
#include "Camera.h"

namespace nsKaEngine {

	Camera::Camera()
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::Init()
	{
		m_target = m_forward * 10000.0f;
	}

	void Camera::Update()
	{
		if (m_isNeedUpdate) {

			Vector2 windowSize = GraphicsEngine::GetInstance()->GetWindowSize();
			float aspect = (float)(windowSize.x / windowSize.y);

			//カメラ行列を作成。
			m_viewMatrix.MakeLookAt(m_position, m_target, m_up);
			//カメラ行列の逆行列を計算。
			m_viewMatrixInv.Inverse(m_viewMatrix);

			//プロジェクション行列を作成。
			if (m_updateProjFunc == e_UpdateProjFunc_Prespective) {
				//透視変換行列を作成。
				m_projectionMatrix.MakeProjecionMatrix(m_fov, aspect, m_near, m_far);
			}
			else {
				//平行投影行列を作成。
				m_projectionMatrix.MakeOrthoProjectionMatrix(m_width, m_height, m_near, m_far);
			}
			//プロジェクション行列の逆行列を計算。
			m_projectionMatrixInv.Inverse(m_projectionMatrix);
			//ビュープロジェクション行列を作成。
			m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
			//ビュープロジェクション行列の逆行列を計算。
			m_viewProjectionMatrixInv.Inverse(m_viewProjectionMatrix);

			//右方向と上方向を設定。
			m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
			m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);

			m_isNeedUpdate = false;
		}
	}
}