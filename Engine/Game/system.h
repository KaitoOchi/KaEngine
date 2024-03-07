#pragma once

/// <summary>
/// デバイスの情報。
/// </summary>
struct DeviceInfo
{
	int		frameRate;				//フレームレート。
	int		windowWidth;			//ウィンドウの横幅。
	int		windowHeight;			//ウィンドウの高さ。
	int		samplingNum;			//マルチサンプリング数。
	int		bgmVolume;				//BGM音量。
	int		sfxVolume;				//SFX音量。
	bool	fullscreen;				//フルスクリーン。
	bool	vsync;					//垂直同期。
	bool	bloom;					//ブルーム。
	float	mouseSensitivity;		//マウス感度。
};

/// <summary>
/// ファイルのセーブ。
/// </summary>
/// <param name="filePath"></param>
/// <param name="saveData"></param>
const int SaveFile(const char* filePath, void* saveData, const size_t size);

/// <summary>
/// ファイルのロード。
/// </summary>
/// <param name="filePath"></param>
/// <param name="saveData"></param>
const int LoadFile(const char* filePath, void* saveData, const size_t size);

/// <summary>
/// デバイス情報を取得。
/// </summary>
/// <param name="deviceInfo"></param>
void GetDeviceInfo(DeviceInfo* deviceInfo);

/// <summary>
/// GLFWウィンドウの作成。
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* CreateGLFWWindow(GLFWwindow* window, DeviceInfo* deviceInfo);

/// <summary>
/// GLFWの初期化。
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* InitGLFW(
	GLFWwindow* window,
	const char* windowName,
	DeviceInfo* deviceInfo
);

/// <summary>
/// エンジンの初期化。
/// </summary>
/// <param name="window"></param>
void InitKaEngine(
	GLFWwindow* window,
	DeviceInfo* deviceInfo
);
