#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ユニフォームバッファ。
	/// </summary>
	class UniformBuffer : Noncopyable
	{
	public:
		GLuint ubo = 0;

		UniformBuffer();
		~UniformBuffer();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		/// <param name="data"></param>
		/// <param name="size"></param>
		void Init(void* data, const int size);

		/// <summary>
		/// 更新処理。
		/// </summary>
		void Update(const int index);

	private:
	};
}

