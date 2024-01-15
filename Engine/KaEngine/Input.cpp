#include "KaEnginePreCompile.h"
#include "Input.h"

namespace nsKaEngine {

	Input* Input::m_instance = nullptr;

	namespace
	{
		struct VirtualPadToKeyPad {
			KeyCode		keyCode;		//�L�[�R�[�h�B
			int			keyNumber;		//glfw�̃L�[�ԍ��B
		};

		struct VirtualPadToMouseButton {
			MouseButton		mouseButton;	//�}�E�X�{�^���B
			int				MouseNumber;	//glfw�̃}�E�X�ԍ��B
		};

		const VirtualPadToKeyPad keyPadTable[e_buttonNum] = {
			{ e_buttonQ,		GLFW_KEY_Q			},
			{ e_buttonW,		GLFW_KEY_W			},
			{ e_buttonE,		GLFW_KEY_E			},
			{ e_buttonR,		GLFW_KEY_R			},
			{ e_buttonT,		GLFW_KEY_T			},
			{ e_buttonY,		GLFW_KEY_Y			},
			{ e_buttonU,		GLFW_KEY_U			},
			{ e_buttonI,		GLFW_KEY_I			},
			{ e_buttonO,		GLFW_KEY_O			},
			{ e_buttonP,		GLFW_KEY_P			},
			{ e_buttonA,		GLFW_KEY_A			},
			{ e_buttonS,		GLFW_KEY_S			},
			{ e_buttonD,		GLFW_KEY_D			},
			{ e_buttonF,		GLFW_KEY_F			},
			{ e_buttonG,		GLFW_KEY_G			},
			{ e_buttonH,		GLFW_KEY_H			},
			{ e_buttonJ,		GLFW_KEY_J			},
			{ e_buttonK,		GLFW_KEY_K			},
			{ e_buttonL,		GLFW_KEY_L			},
			{ e_buttonZ,		GLFW_KEY_Z			},
			{ e_buttonX,		GLFW_KEY_X			},
			{ e_buttonC,		GLFW_KEY_C			},
			{ e_buttonV,		GLFW_KEY_V			},
			{ e_buttonB,		GLFW_KEY_B			},
			{ e_buttonN,		GLFW_KEY_N			},
			{ e_buttonM,		GLFW_KEY_M			},
			{ e_buttonEsc,		GLFW_KEY_ESCAPE		},
		};

		const VirtualPadToMouseButton mouseButtonTable[e_mouseButtonNum] = {
			{ e_mouseButtonLeft,		GLFW_MOUSE_BUTTON_LEFT			},
			{ e_mouseButtonRight,		GLFW_MOUSE_BUTTON_RIGHT			},
			{ e_mouseButtonMiddle,		GLFW_MOUSE_BUTTON_MIDDLE		},
		};
	}

	Input::Input()
	{
		memset(m_keyTrigger, 0, sizeof(m_keyTrigger));
		memset(m_keyPress, 0, sizeof(m_keyPress));
		memset(m_keyRelease, 0, sizeof(m_keyRelease));
		memset(m_mouseTrigger, 0, sizeof(m_mouseTrigger));
		memset(m_mousePress, 0, sizeof(m_mousePress));
		memset(m_mouseRelease, 0, sizeof(m_mouseRelease));
	}

	Input::~Input()
	{

	}

	void Input::Init(GLFWwindow* window)
	{
		m_window = window;
	}

	void Input::Update()
	{
		InputKey();

		InputMouse();
	}

	/// <summary>
	/// �L�[�̓��͏����B
	/// </summary>
	void Input::InputKey()
	{
		for (const VirtualPadToKeyPad& keyPad : keyPadTable) {

			if (glfwGetKey(m_window, keyPad.keyNumber) == GLFW_PRESS) {
				m_keyTrigger[keyPad.keyCode] = 1 ^ m_keyPress[keyPad.keyCode];
				m_keyPress[keyPad.keyCode] = true;
			}
			else {
				m_keyRelease[keyPad.keyCode] = m_keyPress[keyPad.keyCode];
				m_keyPress[keyPad.keyCode] = false;
			}
		}
	}
	
	/// <summary>
	/// �}�E�X�̓��͏����B
	/// </summary>
	void Input::InputMouse()
	{
		//�}�E�X�̍��W���擾�B
		double mouseX, mouseY;
		glfwGetCursorPos(m_window, &mouseX, &mouseY);

		m_mouseAxis = m_mousePosition;

		//��ʂ͈͓̔��Ƀ}�E�X������Ȃ�B
		if (mouseX > 0.0f &&
			mouseX < 1600.0f &&
			mouseY > 0.0f &&
			mouseY < 900.0f
		) {
			//���W��ۑ�����B
			m_mousePosition.x = static_cast<float>(mouseX);
			m_mousePosition.y = static_cast<float>(mouseY);
			
			//���W�̓��͗ʂ��v�Z�B
			m_mouseAxis -= m_mousePosition;
			m_mouseAxis.Normalize();
		}
		else {
			m_mouseAxis = Vector3::Zero;
		}

		if (isnan(m_mouseAxis.x)) {
			m_mouseAxis = Vector3::Zero;
		}

		//�J�[�\�����Œ�Ȃ�A���W��ݒ�B
		if (m_cursorLock) {
			//�J�[�\���̈ʒu���Œ�B
			glfwSetCursorPos(m_window, 1600.0f / 2.0f, 900.0f / 2.0f);
			//���W��ۑ�����B
			glfwGetCursorPos(m_window, &mouseX, &mouseY);
			m_mousePosition.x = static_cast<float>(mouseX);
			m_mousePosition.y = static_cast<float>(mouseY);
		}

		//�}�E�X�{�^���̓��́B
		for (const VirtualPadToMouseButton& mouseButton : mouseButtonTable) {

			if (glfwGetMouseButton(m_window, mouseButton.MouseNumber) == GLFW_PRESS) {
				m_mouseTrigger[mouseButton.mouseButton] = 1 ^ m_mousePress[mouseButton.mouseButton];
				m_mousePress[mouseButton.mouseButton] = true;
			}
			else {
				m_mouseRelease[mouseButton.mouseButton] = m_mousePress[mouseButton.mouseButton];
				m_mousePress[mouseButton.mouseButton] = false;
			}
		}
	}
}