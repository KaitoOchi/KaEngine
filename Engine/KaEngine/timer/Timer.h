#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �^�C���̌v���N���X�B
	/// </summary>
	class Timer : Noncopyable
	{
	public:
		/// <summary>
		/// �v���J�n�B
		/// </summary>
		void Start()
		{
			QueryPerformanceCounter(&m_begin);
		}

		/// <summary>
		/// �v���I���B
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
		/// �o�ߎ��Ԃ��擾�B
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
		LARGE_INTEGER	m_begin = { 0 };		//�J�n���ԁB
		LARGE_INTEGER	m_end = { 0 };			//�I�����ԁB
		LARGE_INTEGER	m_freq = { 0 };			//�����B
		double			m_elapsedSec = 0.0f;	//�o�ߎ��ԁi�b�j�B
		double			m_elapsedMill = 0.0f;	//�o�ߎ��ԁi�~���b�j�B
		double			m_elapsedMicro = 0.0f;	//�o�ߎ��ԁi�}�C�N���b�j�B
	};
}
