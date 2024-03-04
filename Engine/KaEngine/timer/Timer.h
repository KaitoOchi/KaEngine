#pragma once

namespace nsKaEngine {

	/// <summary>
	/// タイムの計測クラス。
	/// </summary>
	class Timer : Noncopyable
	{
	public:
		/// <summary>
		/// 計測開始。
		/// </summary>
		void Start()
		{
			QueryPerformanceCounter(&m_begin);
		}

		/// <summary>
		/// 計測終了。
		/// </summary>
		void Stop()
		{
			QueryPerformanceFrequency(&m_freq);
			QueryPerformanceCounter(&m_end);
			m_elapsedSec = static_cast<double>(m_end.QuadPart - m_begin.QuadPart) / m_freq.QuadPart;
			m_elapsedMill = m_elapsedSec * 1000.0;
			m_elapsedMicro = m_elapsedMill * 1000.0;
		}

		/// <summary>
		/// 経過時間を取得。
		/// </summary>
		/// <returns></returns>
		double GetElapsedSec() const
		{
			return m_elapsedSec;
		}
		double GetElapsedMill() const
		{
			return m_elapsedMill;
		}
		double GetElapsedMicro() const
		{
			return m_elapsedMicro;
		}

	private:
		LARGE_INTEGER	m_begin = { 0 };		//開始時間。
		LARGE_INTEGER	m_end = { 0 };			//終了時間。
		LARGE_INTEGER	m_freq = { 0 };			//周期。
		double			m_elapsedSec = 0.0f;	//経過時間（秒）。
		double			m_elapsedMill = 0.0f;	//経過時間（ミリ秒）。
		double			m_elapsedMicro = 0.0f;	//経過時間（マイクロ秒）。
	};
}
