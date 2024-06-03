#pragma once

namespace nsKaEngine {
	
	/// <summary>
	/// �R���W�����̃��C���t���[���\���N���X�B
	/// </summary>
	class DebugWireFrame : public btIDebugDraw, public Noncopyable
	{
	public:
		DebugWireFrame();
		~DebugWireFrame();

		/// <summary>
		/// �����������B
		/// </summary>
		void Init();

		/// <summary>
		/// �J�n�����B
		/// </summary>
		void Begin();

		/// <summary>
		/// �I�������B
		/// </summary>
		void End();


		void    drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

		void    setDebugMode(int debugMode) override {};

		int     getDebugMode() const override
		{
			return true;
		};

		void    drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {};
		void    reportErrorWarning(const char* warningString) override {};
		void    draw3dText(const btVector3& location, const char* textString) override {}

	private:
		/// <summary>
		/// ���b�V���̏������B
		/// </summary>
		void InitMesh();
		/// <summary>
		/// �V�F�[�_�[�̏������B
		/// </summary>
		void InitShader();
		/// <summary>
		/// �萔�o�b�t�@�̏������B
		/// </summary>
		void InitUniformBuffer();
		/// <summary>
		/// �萔�o�b�t�@�̍X�V�����B
		/// </summary>
		void UniformBufferUpdate();
		/// <summary>
		/// ���_���̒ǉ��B
		/// </summary>
		/// <param name="from">�n�_</param>
		/// <param name="to">�I�_</param>
		/// <param name="color">���̐F</param>
		void AddVertex(
			const btVector3& from,
			const btVector3& to,
			const btVector3& color
		);

	private:
		std::vector<WireFrameVertex>	m_vertexList;					//���_���X�g�B
		Shader							m_shaderProgram;				//�V�F�[�_�[�B
		VAO								m_vao;							//VAO�B
		VBO								m_vbo;							//VBO�B
		UniformBuffer					m_uniformBuffer;				//�萔�o�b�t�@�B
	};
}
