#pragma once

namespace nsKaEngine {
	
	/// <summary>
	/// コリジョンのワイヤフレーム表示クラス。
	/// </summary>
	class DebugWireFrame : public btIDebugDraw, public Noncopyable
	{
	public:
		DebugWireFrame();
		~DebugWireFrame();

		/// <summary>
		/// 初期化処理。
		/// </summary>
		void Init();

		/// <summary>
		/// 開始処理。
		/// </summary>
		void Begin();

		/// <summary>
		/// 終了処理。
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
		/// メッシュの初期化。
		/// </summary>
		void InitMesh();
		/// <summary>
		/// シェーダーの初期化。
		/// </summary>
		void InitShader();
		/// <summary>
		/// 定数バッファの初期化。
		/// </summary>
		void InitUniformBuffer();
		/// <summary>
		/// 定数バッファの更新処理。
		/// </summary>
		void UniformBufferUpdate();
		/// <summary>
		/// 頂点情報の追加。
		/// </summary>
		/// <param name="from">始点</param>
		/// <param name="to">終点</param>
		/// <param name="color">線の色</param>
		void AddVertex(
			const btVector3& from,
			const btVector3& to,
			const btVector3& color
		);

	private:
		std::vector<WireFrameVertex>	m_vertexList;					//頂点リスト。
		Shader							m_shaderProgram;				//シェーダー。
		VAO								m_vao;							//VAO。
		VBO								m_vbo;							//VBO。
		UniformBuffer					m_uniformBuffer;				//定数バッファ。
	};
}
