#pragma once

/// <summary>
/// デバイスの情報。
/// </summary>
struct Config
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
/// <param name="filePath">セーブするファイル名</param>
/// <param name="saveData">格納先の構造体</param>
/// <param name="size">構造体のサイズ</param>
/// <returns>失敗した場合-1を返す</returns>
const int SaveFile(
	const char* filePath,
	void* saveData, 
	const size_t size
);

/// <summary>
/// ファイルのロード。
/// </summary>
/// <param name="filePath">ロードするファイル名</param>
/// <param name="saveData">格納先の構造体</param>
/// <param name="size">構造体のサイズ</param>
/// <returns>失敗した場合-1を返す</returns>
const int LoadFile(
	const char* filePath,
	void* saveData, 
	const size_t size
);

/// <summary>
/// デバイス情報を取得。
/// </summary>
/// <param name="deviceInfo"></param>
void GetConfigFile(Config* config);

/// <summary>
/// GLFWウィンドウの作成。
/// </summary>
/// <param name="window"></param>
/// <param name="deviceInfo"></param>
/// <returns></returns>
GLFWwindow* CreateGLFWWindow(
	GLFWwindow* window,
	Config* deviceInfo
);

/// <summary>
/// GLFWの初期化。
/// </summary>
/// <param name="window"></param>
/// <param name="windowName"></param>
/// <param name="deviceInfo"></param>
/// <returns></returns>
GLFWwindow* InitGLFW(
	GLFWwindow* window,
	const char* windowName,
	Config* deviceInfo
);