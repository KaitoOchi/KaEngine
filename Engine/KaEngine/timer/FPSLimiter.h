#pragma once

#include "timer/Timer.h"
namespace nsKaEngine {

	/// <summary>
	/// FPS�̐��䏈���B
	/// </summary>
	class FPSLimiter : Noncopyable
	{
	public:
		/// <summary>
		/// �J�n�����B
		/// </summary>
		void BeginFrame()
		{
			m_timer.Start();
		}

		/// <summary>
		/// �I�������B
		/// </summary>
		void EndFrame()
		{
			//1�t���[���̍ŏ����Ԃ��v�Z�B
			float frameDeltaTimeMin = 1000.0f / m_maxFPS;
			float restTime = 0;
			do {
				m_timer.Stop();
				restTime = frameDeltaTimeMin - static_cast<int>(m_timer.GetElapsedMill());
			} while (restTime > 1.0f);
		}

		/// <summary>
		/// �ő�FPS��ݒ�B
		/// </summary>
		/// <param name="fps"></param>
		void SetMaxFPS(const int fps)
		{
			m_maxFPS = fps;
		}

		/// <summary>
		/// �ő�FPS���擾�B
		/// </summary>
		/// <returns></returns>
		const int GetMaxFPS() const
		{
			return m_maxFPS;
		}

		const double Get() const
		{
			return m_timer.GetElapsedSec();
		}

	private:
		Timer	m_timer;		//�^�C���v���B
		int		m_maxFPS = 60;	//�ő�FPS�B
	};
}