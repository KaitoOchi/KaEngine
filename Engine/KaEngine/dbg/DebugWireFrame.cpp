#include "KaEnginePreCompile.h"
#include "DebugWireFrame.h"

namespace nsKaEngine {

	DebugWireFrame::DebugWireFrame()
	{
		m_vertexList.reserve(10000);
	}

	DebugWireFrame::~DebugWireFrame()
	{
		m_vao.Delete();
		m_vbo.Delete();
		m_shaderProgram.Delete();
	}

	void DebugWireFrame::Init()
	{
		InitMesh();

		InitShader();

		InitUniformBuffer();
	}

	void DebugWireFrame::InitMesh()
	{
		m_vao.Init();
		m_vao.Bind();

		m_vbo.Init(m_vertexList);

		m_vao.LinkAttribute(m_vbo, 0, 3, GL_FLOAT, sizeof(WireFrameVertex), (void*)0);
		m_vao.LinkAttribute(m_vbo, 1, 3, GL_FLOAT, sizeof(WireFrameVertex), (void*)(3 * sizeof(float)));

		m_vao.UnBind();
		m_vbo.UnBind();
	}

	void DebugWireFrame::InitShader()
	{
		std::array<std::string, ADD_INCLUDE_FILE_MAX> a;

		//シェーダーの初期化。
		m_shaderProgram.Init(
			"Assets/shader/debugWireFrame.vert",
			"Assets/shader/debugWireFrame.frag",
			a
		);
		m_shaderProgram.Activate();
	}

	void DebugWireFrame::InitUniformBuffer()
	{
		m_uniformBuffer.Init(sizeof(Matrix), m_shaderProgram.GetShaderID(), "MatrixUB");
	}

	void DebugWireFrame::UniformBufferUpdate()
	{
		Matrix mVP = g_camera3D->GetViewProjectionMatrix();

		m_uniformBuffer.Update(&mVP, sizeof(Matrix));
	}

	void DebugWireFrame::AddVertex(
		const btVector3& from,
		const btVector3& to,
		const btVector3& color
	) {
		WireFrameVertex vert[2];
		vert[0].position = Vector3(from.x(), from.y(), from.z());
		vert[0].color = Vector3(color.x(), color.y(), color.z());
		vert[1].position = Vector3(to.x(), to.y(), to.z());
		vert[1].color = Vector3(color.x(), color.y(), color.z());

		m_vertexList.emplace_back(vert[0]);
		m_vertexList.emplace_back(vert[1]);
	}

	void DebugWireFrame::Begin()
	{
		m_vertexList.clear();
	}

	void DebugWireFrame::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		AddVertex(from, to, color);
	}

	void DebugWireFrame::End()
	{
		if (m_vertexList.size() == 0) {
			return;
		}

		m_shaderProgram.Activate();

		UniformBufferUpdate();

		m_vao.Bind();
		//頂点情報を格納。
		m_vbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, m_vertexList.size() * sizeof(WireFrameVertex), m_vertexList.data(), GL_DYNAMIC_DRAW);
		//ラインで描画する。
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_vertexList.size()));

		m_vao.UnBind();
		m_vbo.UnBind();
	}
}
