#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ���j�t�H�[���o�b�t�@�B
	/// </summary>
	class UniformBuffer : Noncopyable
	{
	public:
		GLuint ubo = 0;

		UniformBuffer();
		~UniformBuffer();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="data"></param>
		/// <param name="size"></param>
		void Init(void* data, const int size);

		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update(const int index);

	private:
	};
}

