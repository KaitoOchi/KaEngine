#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �A�T�[�g�B
	/// </summary>
	/// <param name="frag">�U�̂Ƃ��ɔ���</param>
	/// <param name="errorCaption">�G���[��</param>
	/// <param name="errorMessage">�G���[���b�Z�[�W</param>
	static inline void KaAssert(
		const bool frag,
		const char* errorCaption,
		const char* errorMessage
	) {
		if (frag) {
			return;
		}
		MessageBoxA(nullptr, errorMessage, errorCaption, MB_OK);
		std::abort();
	}

	/// <summary>
	/// ���O�o�́B
	/// </summary>
	/// <param name="format">�e�L�X�g</param>
	static inline void KaLog(const char* format)
	{
		OutputDebugStringA(format);
	}
}

#ifdef _DEBUG
	#define Ka_Assert(flag, errorCaption, errorMessage) nsKaEngine::KaAssert(flag, errorCaption, errorMessage)
	#define Ka_Log(format) nsKaEngine::Ka_Log(format);
#else
	#define Ka_Assert(flag, errorCaption, errorMessage)
	#define Ka_Log(format)
#endif