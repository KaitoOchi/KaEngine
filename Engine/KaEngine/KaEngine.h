#pragma once

namespace nsKaEngine {

	/// <summary>
	/// エンジンクラス。
	/// </summary>
	class KaEngine : Noncopyable
	{
	public:
		KaEngine();
		~KaEngine();

		/// <summary>
		/// 実行処理。
		/// </summary>
		void Execute();

	private:
	};
}