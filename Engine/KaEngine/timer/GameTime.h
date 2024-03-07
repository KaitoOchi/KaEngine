#pragma once

namespace nsKaEngine {

	/// <summary>
	/// FPS�̐��䏈���B
	/// </summary>
	class GameTime : Noncopyable
	{
	public:
		/// <summary>
		/// �t���[�����[�g���[�h�B
		/// </summary>
		enum EnFrameRateMode {
			e_frameRateMode_Variable,	//�ρB
			e_frameRateMode_Fixed,		//�Œ�B
		};

	public:
		/// <summary>
		/// �t���[�����[�g���[�h��ύX�B
		/// </summary>
		/// <param name="mode"></param>
		void SetFrameRateMode(const EnFrameRateMode mode)
		{
			m_enFrameRateMode = mode;
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

		/// <summary>
		/// �O�t���[������̌o�ߎ��Ԃ��擾�B
		/// </summary>
		/// <returns></returns>
		const float GetFrameDeltaTime() const
		{
			return m_frameDeltaTime;
		}

		/// <summary>
		/// �Q�[���J�n����o�߂����t���[�������擾�B
		/// </summary>
		/// <returns></returns>
		const int GetFrameCount() const
		{
			return m_frameCount;
		}

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
			//�t���[�����[�g���Œ�Ȃ�B
			if (m_enFrameRateMode == e_frameRateMode_Fixed) {
				SpinLock();
			}

			PushFrameDeltaTime();

			m_frameCount++;

			//std::cout << 1.0f / m_frameDeltaTime << std::endl;
		}

	private:
		/// <summary>
		/// �X�s�����b�N���s���B
		/// </summary>
		void SpinLock()
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
		/// 1�t���[���̌o�ߎ��Ԃ��L���[�Ƀv�b�V������B
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
				//���ϒl���Ƃ�B
				m_frameDeltaTime = std::min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
				m_frameDeltaTimeQue.pop_front();
			}
		}

	private:
		Timer				m_timer;				//�^�C���v���B
		EnFrameRateMode		m_enFrameRateMode;		//�t���[�����[�g���[�h�B
		std::list<float>	m_frameDeltaTimeQue;	//1�t���[���̌o�ߎ��ԃ��X�g�B
		int					m_maxFPS = 60;			//�ő�FPS�B
		int					m_frameCount = 0;		//�o�߂����t���[�����B
		float				m_frameDeltaTime = 1.0f / 60.0f;
	};
}