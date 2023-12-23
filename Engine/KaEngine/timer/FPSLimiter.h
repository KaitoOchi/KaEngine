#pragma once

#include "timer/Timer.h"
namespace nsKaEngine {

	/// <summary>
	/// FPSの制御処理。
	/// </summary>
	class FPSLimiter : Noncopyable
	{
	public:
		/// <summary>
		/// 開始処理。
		/// </summary>
		void BeginFrame()
		{
			m_timer.Start();
		}

		/// <summary>
		/// 終了処理。
		/// </summary>
		void EndFrame()
		{
			//1フレームの最小時間を計算。
			float frameDeltaTimeMin = 1000.0f / m_maxFPS;
			float restTime = 0;
			do {
				m_timer.Stop();
				restTime = frameDeltaTimeMin - static_cast<int>(m_timer.GetElapsedMill());
			} while (restTime > 1.0f);
		}

		/// <summary>
		/// 最大FPSを設定。
		/// </summary>
		/// <param name="fps"></param>
		void SetMaxFPS(const int fps)
		{
			m_maxFPS = fps;
		}

		/// <summary>
		/// 最大FPSを取得。
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
		Timer	m_timer;		//タイム計測。
		int		m_maxFPS = 60;	//最大FPS。
	};
}