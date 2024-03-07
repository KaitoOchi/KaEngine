#include "stdafx.h"
#include "system.h"

const int SaveFile(
	const char* filePath,
	void* saveData,
	const size_t size
){
	//�t�@�C�����J���B
	FILE* fp = nullptr;
	errno_t error;
	error = fopen_s(&fp, filePath, "wb");
	if (error != 0) {
		return -1;
	}

	//�t�@�C���̏������݁B
	fwrite(saveData, size, 1, fp);
	fclose(fp);

	return 0;
}

const int LoadFile(
	const char* filePath,
	void* saveData,
	const size_t size
) {
	//�t�@�C�����J���B
	FILE* fp = nullptr;
	errno_t error;
	error = fopen_s(&fp, filePath, "rb");
	if (error != 0) {
		Ka_Log("�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B");
		return -1;
	}

	//�t�@�C���̓ǂݍ��݁B
	fread(saveData, size, 1, fp);
	fclose(fp);

	return 0;
}


/// <summary>
/// �f�o�C�X�̏����擾�B
/// </summary>
void GetDeviceInfo(DeviceInfo* deviceInfo)
{
	//�ݒ�t�@�C���������Ȃ�A�f�o�C�X��񂩂�쐬�B
	if (LoadFile("KaEngine.config", deviceInfo, sizeof(DeviceInfo)) == -1) {

#ifdef _WIN32
		//Window�̃f�o�C�X�����擾�B
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
		//�Z�[�u����B
		if (SaveFile("KaEngine.config", deviceInfo, sizeof(DeviceInfo)) == -1) {
			Ka_Assert(false, "SaveData_Error", "�Z�[�u�f�[�^�̏������݂Ɏ��s���܂����B");
		}
	}
}

/// <summary>
/// GLFW�E�B���h�E�̍쐬�B
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* CreateGLFWWindow(GLFWwindow* window, DeviceInfo* deviceInfo)
{
	//GLFW�̃o�[�W�����ƃv���t�@�C�����w��B
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�_�u���o�b�t�@�����O��L���B
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

	//�}���`�T���v�����O��L���B
	glfwWindowHint(GLFW_SAMPLES, deviceInfo->samplingNum);

	//�E�B���h�E�̃��T�C�Y�s�\�B
	glfwWindowHint(GLFW_RESIZABLE, 0);

	//�E�B���h�E���쐬�B
	window = glfwCreateWindow(
		static_cast<int>(deviceInfo->windowWidth),
		static_cast<int>(deviceInfo->windowHeight),
		"",
		NULL,
		NULL
	);

	if (window == NULL) {
		Ka_Assert(false, "codeError", "GLFW�̃E�B���h�E�쐬�Ɏ��s���܂����B");
		glfwTerminate();
		std::abort();
	}

	glfwMakeContextCurrent(window);

	//����������ݒ�B
	int swapInterval = 0;
	if (deviceInfo->vsync == true) {
		swapInterval = 1;
	}
	glfwSwapInterval(swapInterval);

	return window;
}

/// <summary>
/// GLFW�̏������B
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* InitGLFW(
	GLFWwindow* window,
	const char* windowName,
	DeviceInfo* deviceInfo
) {
	//GLFW�̏������B
	glfwInit();

	//�E�B���h�E�̍쐬�B
	window = CreateGLFWWindow(window, deviceInfo);

	//�E�B���h�E�̖��O�B
	glfwSetWindowTitle(window, windowName);

	gladLoadGL(glfwGetProcAddress);
	glViewport(0, 0, static_cast<int>(deviceInfo->windowWidth), static_cast<int>(deviceInfo->windowHeight));

	//�G���W���̏������B
	InitKaEngine(window, deviceInfo);

	return window;
}

/// <summary>
/// �G���W���̏������B
/// </summary>
/// <param name="window"></param>
void InitKaEngine(GLFWwindow* window, DeviceInfo* deviceInfo)
{

	//�擾�����������ɃG���W�����������B
	KaEngine::CreateInstance(
		window,
		deviceInfo
	);
}