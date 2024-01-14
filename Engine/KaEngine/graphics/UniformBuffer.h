#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ���j�t�H�[���o�b�t�@�B
	/// </summary>
	class UniformBuffer
	{
	public:
		UniformBuffer();
		~UniformBuffer();

		/// <summary>
		/// �����������B
		/// </summary>
		/// <param name="size">�\���̂̃T�C�Y</param>
		/// <param name="shaderID">�V�F�[�_�[�v���O����ID</param>
		/// <param name="blockName">�V�F�[�_�[�ł����Ă���\���̖̂��O</param>
		void Init(
			const int size,
			GLuint shaderID,
			const char* blockName
		);

		/// <summary>
		/// �X�V�����B
		/// </summary>
		/// <param name="data">�\����</param>
		/// <param name="size">�\���̂̃T�C�Y</param>
		void Update(void* data, const int size);

	private:
		GLuint m_ubo = 0;				//UBO�B
		GLuint m_blockIndex = 0;		//�u���b�N�C���f�b�N�X�B
	};
}

