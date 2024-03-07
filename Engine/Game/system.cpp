#include "stdafx.h"
#include "system.h"

const int SaveFile(
	const char* filePath,
	void* saveData,
	const size_t size
){
	//ファイルを開く。
	FILE* fp = nullptr;
	errno_t error;
	error = fopen_s(&fp, filePath, "wb");
	if (error != 0) {
		return -1;
	}

	//ファイルの書き込み。
	fwrite(saveData, size, 1, fp);
	fclose(fp);

	return 0;
}

const int LoadFile(
	const char* filePath,
	void* saveData,
	const size_t size
) {
	//ファイルを開く。
	FILE* fp = nullptr;
	errno_t error;
	error = fopen_s(&fp, filePath, "rb");
	if (error != 0) {
		Ka_Log("ファイルの読み込みに失敗しました。");
		return -1;
	}

	//ファイルの読み込み。
	fread(saveData, size, 1, fp);
	fclose(fp);

	return 0;
}


/// <summary>
/// デバイスの情報を取得。
/// </summary>
void GetDeviceInfo(DeviceInfo* deviceInfo)
{
	//設定ファイルが無いなら、デバイス情報から作成。
	if (LoadFile("KaEngine.config", deviceInfo, sizeof(DeviceInfo)) == -1) {

#ifdef _WIN32
		//Windowのデバイス情報を取得。
		DEVMODE* devMode = new DEVMODE();
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, devMode);

		deviceInfo->frameRate = devMode->dmDisplayFrequency;
		deviceInfo->windowWidth = devMode->dmPelsWidth;
		deviceInfo->windowHeight = devMode->dmPelsHeight;
		deviceInfo->samplingNum = 1;
		deviceInfo->bgmVolume = 1.0f;
		deviceInfo->sfxVolume = 1.0f;
		deviceInfo->fullscreen = false;
		deviceInfo->vsync = false;
		deviceInfo->bloom = true;
		deviceInfo->mouseSensitivity = 1.0f;

		delete devMode;

#else

		deviceInfo->frameRate = 60;
		deviceInfo->windowWidth = 1280;
		deviceInfo->windowHeight = 920;
		deviceInfo->samplingNum = 1;
		deviceInfo->bgmVolume = 1.0f;
		deviceInfo->sfxVolume = 1.0f;
		deviceInfo->fullscreen = false;
		deviceInfo->vsync = false;
		deviceInfo->bloom = true;
		deviceInfo->mouseSensitivity = 1.0f;

#endif
		//セーブする。
		if (SaveFile("KaEngine.config", deviceInfo, sizeof(DeviceInfo)) == -1) {
			Ka_Assert(false, "SaveData_Error", "セーブデータの書き込みに失敗しました。");
		}
	}
}

/// <summary>
/// GLFWウィンドウの作成。
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* CreateGLFWWindow(GLFWwindow* window, DeviceInfo* deviceInfo)
{
	//GLFWのバージョンとプロファイルを指定。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//ダブルバッファリングを有効。
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

	//マルチサンプリングを有効。
	glfwWindowHint(GLFW_SAMPLES, deviceInfo->samplingNum);

	//ウィンドウのリサイズ不可能。
	glfwWindowHint(GLFW_RESIZABLE, 0);

	//ウィンドウを作成。
	window = glfwCreateWindow(
		static_cast<int>(deviceInfo->windowWidth),
		static_cast<int>(deviceInfo->windowHeight),
		"",
		NULL,
		NULL
	);

	if (window == NULL) {
		Ka_Assert(false, "codeError", "GLFWのウィンドウ作成に失敗しました。");
		glfwTerminate();
		std::abort();
	}

	glfwMakeContextCurrent(window);

	//垂直同期を設定。
	int swapInterval = 0;
	if (deviceInfo->vsync == true) {
		swapInterval = 1;
	}
	glfwSwapInterval(swapInterval);

	return window;
}

/// <summary>
/// GLFWの初期化。
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* InitGLFW(
	GLFWwindow* window,
	const char* windowName,
	DeviceInfo* deviceInfo
) {
	//GLFWの初期化。
	glfwInit();

	//ウィンドウの作成。
	window = CreateGLFWWindow(window, deviceInfo);

	//ウィンドウの名前。
	glfwSetWindowTitle(window, windowName);

	gladLoadGL(glfwGetProcAddress);
	glViewport(0, 0, static_cast<int>(deviceInfo->windowWidth), static_cast<int>(deviceInfo->windowHeight));

	//エンジンの初期化。
	InitKaEngine(window, deviceInfo);

	return window;
}

/// <summary>
/// エンジンの初期化。
/// </summary>
/// <param name="window"></param>
void InitKaEngine(GLFWwindow* window, DeviceInfo* deviceInfo)
{

	//取得した情報を元にエンジンを初期化。
	KaEngine::CreateInstance(
		window,
		deviceInfo
	);
}