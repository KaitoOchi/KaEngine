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

		const VirtualPadToKeyPad keyPadTable[enButtonNum] = {
			{ enButtonQ,		GLFW_KEY_Q			},
			{ enButtonW,		GLFW_KEY_W			},
			{ enButtonE,		GLFW_KEY_E			},
			{ enButtonR,		GLFW_KEY_R			},
			{ enButtonT,		GLFW_KEY_T			},
			{ enButtonY,		GLFW_KEY_Y			},
			{ enButtonU,		GLFW_KEY_U			},
			{ enButtonI,		GLFW_KEY_I			},
			{ enButtonO,		GLFW_KEY_O			},
			{ enButtonP,		GLFW_KEY_P			},
			{ enButtonA,		GLFW_KEY_A			},
			{ enButtonS,		GLFW_KEY_S			},
			{ enButtonD,		GLFW_KEY_D			},
			{ enButtonF,		GLFW_KEY_F			},
			{ enButtonG,		GLFW_KEY_G			},
			{ enButtonH,		GLFW_KEY_H			},
			{ enButtonJ,		GLFW_KEY_J			},
			{ enButtonK,		GLFW_KEY_K			},
			{ enButtonL,		GLFW_KEY_L			},
			{ enButtonZ,		GLFW_KEY_Z			},
			{ enButtonX,		GLFW_KEY_X			},
			{ enButtonC,		GLFW_KEY_C			},
			{ enButtonV,		GLFW_KEY_V			},
			{ enButtonB,		GLFW_KEY_B			},
			{ enButtonN,		GLFW_KEY_N			},
			{ enButtonM,		GLFW_KEY_M			},
			{ enButtonEsc,		GLFW_KEY_ESCAPE		},
		};

		const VirtualPadToMouseButton mouseButtonTable[enMouseButtonNum] = {
			{ enMouseButtonLeft,		GLFW_MOUSE_BUTTON_LEFT			},
			{ enMouseButtonRight,		GLFW_MOUSE_BUTTON_RIGHT			},
			{ enMouseButtonMiddle,		GLFW_MOUSE_BUTTON_MIDDLE		},
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