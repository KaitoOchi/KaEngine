#pragma once

namespace nsKaEngine {

	/// <summary>
	/// アサート。
	/// </summary>
	/// <param name="frag">偽のときに発生</param>
	/// <param name="errorCaption">エラー名</param>
	/// <param name="errorMessage">エラーメッセージ</param>
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
	/// ログ出力。
	/// </summary>
	/// <param name="format">テキスト</param>
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