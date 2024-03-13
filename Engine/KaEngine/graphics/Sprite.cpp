#include "KaEnginePreCompile.h"
#include "Sprite.h"

namespace nsKaEngine {

	namespace
	{
		const Matrix SPRITE_VIEW_MATRIX = Matrix(		//ビュー行列。
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f
		);
	}

	Sprite::Sprite()
	{
		memset(m_texture, 0, sizeof(m_texture));
	}

	Sprite::~Sprite()
	{
		m_vao.Delete();
		m_vbo.Delete();
		m_ebo.Delete();
		m_shaderProgram.Delete();
	}

	void Sprite::Init(SpriteInitData& initData)
	{
		//画像のハーフサイズを設定。
		m_size.Set(static_cast<float>(initData.width), static_cast<float>(initData.height));
		m_size.Scale(0.5f);

		InitTexture(initData);

		InitVertexBufferAndElementsBuffer();

		InitShader(initData);

		InitUniformBuffer(initData);
	}

	void Sprite::InitTexture(SpriteInitData& initData)
	{
		int texNum = 0;

		//ファイルからテクスチャを取得。
		if (initData.filePath.empty() == false) {
			auto texture = KaEngine::GetInstance()->GetTextureBank(initData.filePath.c_str());
			if (texture == nullptr) {
				texture = new Texture;
				texture->Init(initData.filePath.c_str(), GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
				KaEngine::GetInstance()->RegistTextureBank(initData.filePath.c_str(), texture);
				m_texture[0] = texture;
			}
			m_texture[0]->TexUnit(&m_shaderProgram, "texture", 0);

			++texNum;
		}
		//指定されたテクスチャから取得。
		else if (initData.textures[0] != nullptr) {

			for (texNum = texNum; texNum < initData.textures.size(); ++texNum) {
				m_texture[texNum] = initData.textures[texNum];
				m_texture[texNum]->TexUnit(&m_shaderProgram, "texture", texNum);
			}
		}
		else {
			Ka_Assert(false, "codeError", "テクスチャの初期化に失敗しました。");
		}
	}

	void Sprite::InitVertexBufferAndElementsBuffer()
	{
		std::vector<SpriteVertex> verts = {
			{
				Vector4(-m_size.x, -m_size.y, 0.0f, 1.0f),
				Vector2(0.0f, 0.0f),
			},
			{
				Vector4(-m_size.x, m_size.y, 0.0f, 1.0f),
				Vector2(0.0f, 1.0f),
			},
			{
				Vector4(m_size.x, m_size.y, 0.0f, 1.0f),
				Vector2(1.0f, 1.0f)
			},
			{
				Vector4(m_size.x, -m_size.y, 0.0f, 1.0f),
				Vector2(1.0f, 0.0f)
		} };
		std::vector <GLuint> ind = {
			{
				0, 2, 1,
				0, 3, 2
		} };
		m_indices = ind;

		m_vao.Init();
		m_vao.Bind();

		m_vbo.Init(verts);
		m_ebo.Init(ind);

		// Links VBO to VAO
		m_vao.LinkAttribute(m_vbo, 0, 4, GL_FLOAT, sizeof(SpriteVertex), (void*)0);
		m_vao.LinkAttribute(m_vbo, 1, 2, GL_FLOAT, sizeof(SpriteVertex), (void*)(4 * sizeof(float)));

		m_vao.UnBind();
		m_vbo.UnBind();
		m_ebo.UnBind();
	}

	void Sprite::InitShader(SpriteInitData& initData)
	{
		auto shader = KaEngine::GetInstance()->GetShaderBank(initData.vertexFilePath.c_str());
		if (shader == nullptr) {
			shader = new Shader();
			shader->Init(initData.vertexFilePath.c_str(), initData.fragmentFilePath.c_str(), initData.addIncludeFile);
			
		}
		m_shaderProgram = shader;
		m_shaderProgram->Activate();
	}

	void Sprite::InitUniformBuffer(SpriteInitData& initData)
	{
		//スプライト用UBの作成。
		m_spriteUniformBuffer.Init(sizeof(SpriteUB), m_shaderProgram.GetShaderID(), "SpriteUB");

		//ユーザー拡張用UBの作成。
		if (initData.expandUniformBuffer != nullptr) {
			m_expandUniformBuffer.Init(initData.expandUniformBufferSize, m_shaderProgram.GetShaderID(), initData.expandUniformBufferName.c_str());
			m_expandUB = initData.expandUniformBuffer;
			m_expandUBSize = initData.expandUniformBufferSize;
		}
	}

	void Sprite::Update(
		const Vector3& pos,
		const Quaternion& rot,
		const Vector3& scale,
		const Vector2& pivot
	) {
		//ローカル座標を求める。
		Vector2Int viewPort = GraphicsEngine::GetInstance()->GetWindowSize();
		Vector3 localPosition = pos;
		localPosition.x /= viewPort.x;
		localPosition.y /= viewPort.y;

		//ローカルピボットを求める。
		Vector2 localPivot = pivot;
		localPivot.x -= 1.0f;
		localPivot.y -= 1.0f;
		localPivot.Clamp(-2.0f, 0.0f);
		localPivot.Scale(0.001f);

		Matrix mPivotTrans;
		mPivotTrans.MakeTranslate(Vector3(
			m_size.x * localPivot.x,
			m_size.y * localPivot.y,
			0.0f
		));

		Matrix mTrans, mRot, mScale;
		mTrans.MakeTranslate(localPosition);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);

		m_worldMatrix = mTrans;
		m_worldMatrix = m_worldMatrix * mPivotTrans;
		m_worldMatrix = m_worldMatrix * mScale;
		m_worldMatrix = m_worldMatrix * mRot;
	}

	void Sprite::Draw()
	{
		Vector2Int viewPort = GraphicsEngine::GetInstance()->GetWindowSize();

		//プロジェクション行列を作成。
		Matrix projMatrix;
		projMatrix.MakeOrthoProjectionMatrix(
			static_cast<float>(viewPort.x),
			static_cast<float>(viewPort.y),
			0.1f,
			1.0f
		);

		//モデル用UniformBufferの更新。
		m_spriteUB.mvp = m_worldMatrix * SPRITE_VIEW_MATRIX * projMatrix;
		m_spriteUB.mulColor = m_mulColor;

		m_shaderProgram.Activate();
		//定数バッファの設定。
		m_spriteUniformBuffer.Update(&m_spriteUB, sizeof(SpriteUB));
		if (m_expandUB != nullptr) {
			m_expandUniformBuffer.Update(m_expandUB, m_expandUBSize);
		}

		m_vao.Bind();

		m_texture[0]->Bind(0);

		// Draw the triangles using the GL_TRIANGLES primive
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
	}
}