#pragma once

namespace nsKaEngine {

	/// <summary>
	/// FPSの制御処理。
	/// </summary>
	class GameTime : Noncopyable
	{
	public:
		/// <summary>
		/// フレームレートモード。
		/// </summary>
		enum EnFrameRateMode {
			e_frameRateMode_Variable,	//可変。
			e_frameRateMode_Fixed,		//固定。
		};

	public:
		/// <summary>
		/// フレームレートモードを変更。
		/// </summary>
		/// <param name="mode"></param>
		void SetFrameRateMode(const EnFrameRateMode mode)
		{
			m_enFrameRateMode = mode;
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

		/// <summary>
		/// 前フレームからの経過時間を取得。
		/// </summary>
		/// <returns></returns>
		const float GetFrameDeltaTime() const
		{
			return m_frameDeltaTime;
		}

		/// <summary>
		/// ゲーム開始から経過したフレーム数を取得。
		/// </summary>
		/// <returns></returns>
		const int GetFrameCount() const
		{
			return m_frameCount;
		}

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
			//フレームレートが固定なら。
			if (m_enFrameRateMode == e_frameRateMode_Fixed) {
				SpinLock();
			}

			PushFrameDeltaTime();

			m_frameCount++;

			//std::cout << 1.0f / m_frameDeltaTime << std::endl;
		}

	private:
		/// <summary>
		/// スピンロックを行う。
		/// </summary>
		void SpinLock()
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
		/// 1フレームの経過時間をキューにプッシュする。
		/// </summary>
		void PushFrameDeltaTime()
		{
			m_timer.Stop();
			m_frameDeltaTimeQue.emplace_back(static_cast<float>(m_timer.GetElapsedSec()));
			if (m_frameDeltaTimeQue.size() > 30.0f) {
				float totalTime = 0.0f;
				for (auto time : m_frameDeltaTimeQue) {
					totalTime += time;
				}
				//平均値をとる。
				m_frameDeltaTime = std::min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
				m_frameDeltaTimeQue.pop_front();
			}
		}

	private:
		Timer				m_timer;				//タイム計測。
		EnFrameRateMode		m_enFrameRateMode;		//フレームレートモード。
		std::list<float>	m_frameDeltaTimeQue;	//1フレームの経過時間リスト。
		int					m_maxFPS = 60;			//最大FPS。
		int					m_frameCount = 0;		//経過したフレーム数。
		float				m_frameDeltaTime = 1.0f / 60.0f;
	};
}