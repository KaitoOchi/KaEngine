#include "KaEnginePreCompile.h"
#include "KaEngine.h"

namespace nsKaEngine {

	KaEngine*	KaEngine::m_instance = nullptr;		//エンジンクラス。
	Camera*		g_camera3D = nullptr;				//カメラクラス。
	GameTime*	g_gameTime = nullptr;				//時間制御クラス。

	//頂点座標。
	Vertex vertices[] =
	{ //               COORDINATES				/            NORMALS          /           COLORS         /   TEXTURE COORDINATES    //
		Vertex{Vector3(-1000.0f, 0.0f,  1000.0f),	Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f)},
		Vertex{Vector3(-1000.0f, 0.0f, -1000.0f),	Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)},
		Vertex{Vector3(1000.0f, 0.0f, -1000.0f),	Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)},
		Vertex{Vector3(1000.0f, 0.0f,  1000.0f),	Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f)}
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	Vertex pyramidVertices[] =
	{ //            COORDINATES				  /            NORMALS			 /           COLORS         /    TEXTURE COORDINATES	//
		Vertex{Vector3(-50.5f, 0.0f, 50.5f),	Vector3(0.0f, -1.0f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(0.0f, 0.0f)},
		Vertex{Vector3(-50.5f, 0.0f, -50.5f),	Vector3(0.0f, -1.0f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(0.0f, 5.0f)},
		Vertex{Vector3(50.5f, 0.0f, -50.5f),	Vector3(0.0f, -1.0f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(5.0f, 5.0f)},
		Vertex{Vector3(50.5f, 0.0f, 50.5f),		Vector3(0.0f, -1.0f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(5.0f, 0.0f)},

		Vertex{Vector3(-50.5f, 0.0f, 50.5f),	Vector3(-0.8f, 0.5f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(0.0f, 0.0f)},
		Vertex{Vector3(-50.5f, 0.0f, -50.5f),	Vector3(-0.8f, 0.5f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(5.0f, 0.0f)},
		Vertex{Vector3(0.0f, 80.8f, 0.0f),		Vector3(-0.8f, 0.5f, 0.0f), Vector3(0.92f, 0.86f, 0.76f), Vector2(2.5f, 5.0f)},

		Vertex{Vector3(-50.5f, 0.0f, -50.5f),	Vector3(0.0f, 0.5f, -0.8f), Vector3(0.83f, 0.70f, 0.44f), Vector2(5.0f, 0.0f)},
		Vertex{Vector3(50.5f, 0.0f, -50.5f),	Vector3(0.0f, 0.5f, -0.8f), Vector3(0.83f, 0.70f, 0.44f), Vector2(0.0f, 0.0f)},
		Vertex{Vector3(0.0f, 80.8f, 0.0f),		Vector3(0.0f, 0.5f, -0.8f), Vector3(0.92f, 0.86f, 0.76f), Vector2(2.5f, 5.0f)},

		Vertex{Vector3(50.5f, 0.0f, -50.5f),	Vector3(0.8f, 0.5f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(0.0f, 0.0f)},
		Vertex{Vector3(50.5f, 0.0f, 50.5f),		Vector3(0.8f, 0.5f, 0.0f), Vector3(0.83f, 0.70f, 0.44f), Vector2(5.0f, 0.0f)},
		Vertex{Vector3(0.0f, 80.8f, 0.0f),		Vector3(0.8f, 0.5f, 0.0f), Vector3(0.92f, 0.86f, 0.76f), Vector2(2.5f, 5.0f)},

		Vertex{Vector3(50.5f, 0.0f, 50.5f),		Vector3(0.0f, 0.5f, 0.8f), Vector3(0.83f, 0.70f, 0.44f), Vector2(5.0f, 0.0f)},
		Vertex{Vector3(-50.5f, 0.0f, 50.5f),	Vector3(0.0f, 0.5f, 0.8f), Vector3(0.83f, 0.70f, 0.44f), Vector2(0.0f, 0.0f)},
		Vertex{Vector3(0.0f, 80.8f, 0.0f),		Vector3(0.0f, 0.5f, 0.8f), Vector3(0.92f, 0.86f, 0.76f), Vector2(2.5f, 5.0f)}
	};

	// Indices for vertices order
	GLuint pyramidIndices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	Vertex lightVertices[] =
	{ //     COORDINATES     //
		Vertex{Vector3(-10.0f, -10.0f,  10.0f)},
		Vertex{Vector3(-10.0f, -10.0f, -10.0f)},
		Vertex{Vector3(10.0f, -10.0f, -10.0f)},
		Vertex{Vector3(10.0f, -10.0f,  10.0f)},
		Vertex{Vector3(-10.0f,  10.0f,  10.0f)},
		Vertex{Vector3(-10.0f,  10.0f, -10.0f)},
		Vertex{Vector3(10.0f,  10.0f, -10.0f)},
		Vertex{Vector3(10.0f,  10.0f,  10.0f)}
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	const char* TEXTURE_FILE_PATH[3] = 
	{ 
		"Assets/sprite/nullAlbedoMap.png",
		"Assets/sprite/nullNormalMap.png",
		"Assets/sprite/nullMetallicSmoothMap.png"
	};

	KaEngine::KaEngine()
	{
		memset(&m_texture, 0, sizeof(m_texture));
	}

	KaEngine::~KaEngine()
	{

	}

	void KaEngine::Init(
		GLFWwindow* window,
		Config* config
	) {
		m_config = config;

		//カメラの初期化。
		g_camera3D = new Camera;
		g_camera3D->Init();

		//時間制御クラスの初期化。
		g_gameTime = new GameTime;
		g_gameTime->SetFrameRateMode(GameTime::e_frameRateMode_Fixed);
		g_gameTime->SetMaxFPS(config->frameRate);

		GraphicsEngine::CreateInstance(window, config);
		Input::CreateInstance();
		GameObjectManager::CreateInstance();
		PhysicsEngine::CreateInstance();

		//床モデルの生成。
		ModelInitData modelInitData;
		modelInitData.vertexShaderFilePath = "Assets/shader/default.vert";
		modelInitData.fragmentShaderFilePath = "Assets/shader/default.frag";
		modelInitData.addIncludeFile[0] = "PBRLighting.h";
		modelInitData.addIncludeFile[1] = "PBRLighting_struct.h";
		modelInitData.expandUniformBuffer = &m_lightUB;
		modelInitData.expandUniformBufferSize = sizeof(LightUB);
		modelInitData.expandUniformBufferName = "LightUB";


		for (int i = 0; i < 3; ++i) {
			//テクスチャーの初期化。
			m_texture[i] = KaEngine::GetInstance()->GetTextureBank(TEXTURE_FILE_PATH[i]);
			if (m_texture[i] == nullptr) {
				m_texture[i] = new Texture;
				m_texture[i]->Init(TEXTURE_FILE_PATH[i], GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
				KaEngine::GetInstance()->RegistTextureBank(TEXTURE_FILE_PATH[i], m_texture[i]);
			}
			m_textures.emplace_back(m_texture[i]);
		}

		std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
		std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
		// Create floor mesh
		m_floorMesh.Init(
			verts,
			ind,
			m_textures,
			"",
			modelInitData.vertexShaderFilePath,
			modelInitData.fragmentShaderFilePath,
			modelInitData.addIncludeFile,
			modelInitData.expandUniformBuffer,
			modelInitData.expandUniformBufferSize,
			modelInitData.expandUniformBufferName
		);

		m_floorPos = Vector3(0.0f, 0.0f, 0.0f);
		m_floorModel.MakeTranslate(m_floorPos);


		//四角形モデルの生成。
		std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
		std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
		// Create light mesh
		m_lightMesh.Init(
			lightVerts,
			lightInd,
			m_textures,
			"",
			"Assets/shader/light.vert",
			"Assets/shader/light.frag",
			modelInitData.addIncludeFile,
			nullptr,
			modelInitData.expandUniformBufferSize,
			modelInitData.expandUniformBufferName
		);
		m_lightPos = Vector3(50.0f, 100.0f, 50.0f);
		m_lightModel.MakeTranslate(m_lightPos);


		//ピラミッドモデルの生成。
		std::vector <Vertex> pyramidVerts(pyramidVertices, pyramidVertices + sizeof(pyramidVertices) / sizeof(Vertex));
		std::vector <GLuint> pyramidInd(pyramidIndices, pyramidIndices + sizeof(pyramidIndices) / sizeof(GLuint));

		m_pyramidMesh.Init(
			pyramidVerts,
			pyramidInd,
			m_textures,
			"",
			modelInitData.vertexShaderFilePath,
			modelInitData.fragmentShaderFilePath,
			modelInitData.addIncludeFile,
			modelInitData.expandUniformBuffer,
			modelInitData.expandUniformBufferSize,
			modelInitData.expandUniformBufferName
		);

		m_pyramidPos = Vector3(-50.0f, 50.0f, 0.0f);
		m_pyramidScale = Vector3::One;
		m_pyramidModel.MakeTranslate(m_pyramidPos);


		//スプライトの生成。
		SpriteInitData spriteInitData;
		spriteInitData.filePath = "Assets/sprite/circle.png";
		spriteInitData.vertexFilePath = "Assets/shader/sprite.vert";
		spriteInitData.fragmentFilePath = "Assets/shader/sprite.frag";
		spriteInitData.width = 256;
		spriteInitData.height = 256;
		m_sprite.Init(spriteInitData);


		//ライト用構造体の設定。
		m_lightUB.dirLig.dirDirection = Vector3(0.0f, -0.5f, -1.0f);
		m_lightUB.dirLig.dirDirection.Normalize();
		m_lightUB.dirLig.dirColor = Vector3(0.5f, 0.5f, 0.5f);
		m_lightUB.dirLig.ambient = 0.2f;
		m_lightUB.ptLig.ptPosition = m_lightPos;
		m_lightUB.ptLig.ptColor = Vector3(3.0f, 0.0f, 0.0f);
		m_lightUB.ptLig.ptRange = 300.0f;



		m_sphereGhostObject.CreateSphere(
			Vector3(-150.0f, 50.0f, 0.0f),
			Quaternion::Identity,
			10.0f
		);

	}

	void KaEngine::Execute()
	{
		auto& renderContext = GraphicsEngine::GetInstance()->GetRenderContext();

		Input::GetInstance()->Update();

		GameObjectManager::GetInstance()->ExecuteUpdate();

		PhysicsEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
	}

	void KaEngine::BeginFrame()
	{
		g_gameTime->BeginFrame();

		Input::GetInstance()->BeginFrame();

		PhysicsEngine::GetInstance()->BeginFrame();
	}

	void KaEngine::EndFrame()
	{
		//ライト用構造体の更新。
		m_lightUB.eyePos = g_camera3D->GetPosition();

		m_rotation.SetRotationDegY(m_timer);

		//ピラミッドモデルのモデル。
		Matrix mTrans, mRot, mScale;
		mTrans.MakeTranslate(m_pyramidPos);
		mRot.MakeRotationFromQuaternion(m_rotation);
		mScale.MakeScaling(m_pyramidScale);
		m_pyramidModel = mTrans * mScale * mRot;

		RenderTarget& rt = GraphicsEngine::GetInstance()->GetRenderTarget();

		GraphicsEngine::GetInstance()->GetRenderContext().BindRenderTarget(rt);

		GraphicsEngine::GetInstance()->GetRenderContext().ClearRenderTarget();

		m_floorMesh.Draw(m_floorModel, g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());

		m_pyramidMesh.Draw(m_pyramidModel, g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());

		m_lightMesh.Draw(m_lightModel, g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());

		float dt = g_gameTime->GetFrameDeltaTime();
		m_timer += 100.0f * dt;

		Quaternion rot;
		//rot.SetRotationDegZ(m_timer);

		m_sprite.Update(
			Vector3(1000.0f, 0.0f, 0.0f),
			rot,
			Vector3(0.5f, 0.5f, 0.0f),
			Vector2(0.0f, 0.0f)
		);

		auto& rc = GraphicsEngine::GetInstance()->GetRenderContext();
		m_sprite.Draw(rc);

		PhysicsEngine::GetInstance()->EndFrame();

		if (Input::GetInstance()->GetKey(KeyCode::e_buttonR)) {
			m_pyramidMesh.Delete();
		}

		GraphicsEngine::GetInstance()->GetRenderContext().UnBindRenderTarget();

		GraphicsEngine::GetInstance()->Test();

		//Swap the back buffer with the front buffer
		glfwSwapBuffers(GraphicsEngine::GetInstance()->GetWindow());

		g_gameTime->EndFrame();
	}

	void KaEngine::Delete()
	{
		GraphicsEngine::DeleteInstance();
		Input::DeleteInstance();
		GameObjectManager::DeleteInstance();
		PhysicsEngine::DeleteInstance();

		m_floorMesh.Delete();
		m_lightMesh.Delete();
		m_pyramidMesh.Delete();
	}
}
