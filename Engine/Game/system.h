#pragma once

/// <summary>
/// �f�o�C�X�̏��B
/// </summary>
struct DeviceInfo
{
	int		frameRate;				//�t���[�����[�g�B
	int		windowWidth;			//�E�B���h�E�̉����B
	int		windowHeight;			//�E�B���h�E�̍����B
	int		samplingNum;			//�}���`�T���v�����O���B
	int		bgmVolume;				//BGM���ʁB
	int		sfxVolume;				//SFX���ʁB
	bool	fullscreen;				//�t���X�N���[���B
	bool	vsync;					//���������B
	bool	bloom;					//�u���[���B
	float	mouseSensitivity;		//�}�E�X���x�B
};

/// <summary>
/// �t�@�C���̃Z�[�u�B
/// </summary>
/// <param name="filePath"></param>
/// <param name="saveData"></param>
const int SaveFile(const char* filePath, void* saveData, const size_t size);

/// <summary>
/// �t�@�C���̃��[�h�B
/// </summary>
/// <param name="filePath"></param>
/// <param name="saveData"></param>
const int LoadFile(const char* filePath, void* saveData, const size_t size);

/// <summary>
/// �f�o�C�X�����擾�B
/// </summary>
/// <param name="deviceInfo"></param>
void GetDeviceInfo(DeviceInfo* deviceInfo);

/// <summary>
/// GLFW�E�B���h�E�̍쐬�B
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* CreateGLFWWindow(GLFWwindow* window, DeviceInfo* deviceInfo);

/// <summary>
/// GLFW�̏������B
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* InitGLFW(
	GLFWwindow* window,
	const char* windowName,
	DeviceInfo* deviceInfo
);

/// <summary>
/// �G���W���̏������B
/// </summary>
/// <param name="window"></param>
void InitKaEngine(
	GLFWwindow* window,
	DeviceInfo* deviceInfo
);
