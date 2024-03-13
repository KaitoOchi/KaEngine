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
			{ e_buttonSpace,		GLFW_KEY_SPACE			},
			{ e_buttonApostrophe,	GLFW_KEY_APOSTROPHE		},
			{ e_buttonComma,		GLFW_KEY_COMMA			},
			{ e_buttonMinus,		GLFW_KEY_MINUS			},
			{ e_buttonPeriod,		GLFW_KEY_PERIOD			},
			{ e_buttonSlash,		GLFW_KEY_SLASH			},
			{ e_buttonBackSlash,	GLFW_KEY_BACKSLASH		},
			{ e_buttonSemicolon,	GLFW_KEY_SEMICOLON		},
			{ e_buttonEqual,		GLFW_KEY_EQUAL			},
			{ e_buttonLeftBracket,	GLFW_KEY_LEFT_BRACKET	},
			{ e_buttonRightBracket,	GLFW_KEY_RIGHT_BRACKET	},
			{ e_buttonGraveAccent,	GLFW_KEY_GRAVE_ACCENT	},
			{ e_button0,			GLFW_KEY_0				},
			{ e_button1,			GLFW_KEY_1				},
			{ e_button2,			GLFW_KEY_2				},
			{ e_button3,			GLFW_KEY_3				},
			{ e_button4,			GLFW_KEY_4				},
			{ e_button5,			GLFW_KEY_5				},
			{ e_button6,			GLFW_KEY_6				},
			{ e_button7,			GLFW_KEY_7				},
			{ e_button8,			GLFW_KEY_8				},
			{ e_button9,			GLFW_KEY_9				},
			{ e_buttonQ,			GLFW_KEY_Q				},
			{ e_buttonW,			GLFW_KEY_W				},
			{ e_buttonE,			GLFW_KEY_E				},
			{ e_buttonR,			GLFW_KEY_R				},
			{ e_buttonT,			GLFW_KEY_T				},
			{ e_buttonY,			GLFW_KEY_Y				},
			{ e_buttonU,			GLFW_KEY_U				},
			{ e_buttonI,			GLFW_KEY_I				},
			{ e_buttonO,			GLFW_KEY_O				},
			{ e_buttonP,			GLFW_KEY_P				},
			{ e_buttonA,			GLFW_KEY_A				},
			{ e_buttonS,			GLFW_KEY_S				},
			{ e_buttonD,			GLFW_KEY_D				},
			{ e_buttonF,			GLFW_KEY_F				},
			{ e_buttonG,			GLFW_KEY_G				},
			{ e_buttonH,			GLFW_KEY_H				},
			{ e_buttonJ,			GLFW_KEY_J				},
			{ e_buttonK,			GLFW_KEY_K				},
			{ e_buttonL,			GLFW_KEY_L				},
			{ e_buttonZ,			GLFW_KEY_Z				},
			{ e_buttonX,			GLFW_KEY_X				},
			{ e_buttonC,			GLFW_KEY_C				},
			{ e_buttonV,			GLFW_KEY_V				},
			{ e_buttonB,			GLFW_KEY_B				},
			{ e_buttonN,			GLFW_KEY_N				},
			{ e_buttonM,			GLFW_KEY_M				},
			{ e_buttonEsc,			GLFW_KEY_ESCAPE			},
			{ e_buttonEnter,		GLFW_KEY_ENTER			},
			{ e_buttonTab,			GLFW_KEY_TAB			},
			{ e_buttonBackSpace,	GLFW_KEY_BACKSPACE		},
			{ e_buttonRight,		GLFW_KEY_RIGHT			},
			{ e_buttonLeft,			GLFW_KEY_LEFT			},
			{ e_buttonUp,			GLFW_KEY_UP				},
			{ e_buttonDown,			GLFW_KEY_DOWN			},
			{ e_buttonLeftShift,	GLFW_KEY_LEFT_SHIFT		},
			{ e_buttonRightShift,	GLFW_KEY_RIGHT_SHIFT	},
			{ e_buttonLeftCtrl,		GLFW_KEY_LEFT_CONTROL	},
			{ e_buttonRightCtrl,	GLFW_KEY_RIGHT_CONTROL	},
			{ e_buttonLeftAlt,		GLFW_KEY_LEFT_ALT		},
			{ e_buttonRightAlt,		GLFW_KEY_RIGHT_ALT		},
		};

		const VirtualPadToMouseButton mouseButtonTable[e_mouseButtonNum] = {
			{ e_mouseButtonLeft,		GLFW_MOUSE_BUTTON_LEFT			},
			{ e_mouseButtonRight,		GLFW_MOUSE_BUTTON_RIGHT			},
			{ e_mouseButtonMiddle,		GLFW_MOUSE_BUTTON_MIDDLE		},
		};
	}

	static void InputMouseWheel(GLFWwindow* window, double x, double y)
	{
		Input::GetInstance()->SetCallBackMouseWheelEvent(static_cast<float>(y));
	}

	Input::Input()
	{
		//�z��̏������B
		memset(m_mouseTrigger, 0, sizeof(m_mouseTrigger));
		memset(m_mousePress, 0, sizeof(m_mousePress));
		memset(m_mouseRelease, 0, sizeof(m_mouseRelease));
	}

	Input::~Input()
	{

	}

	void Input::Init()
	{
		auto window = GraphicsEngine::GetInstance()->GetWindow();
		//�}�E�X�z�C�[���̓��͂��R�[���o�b�N�`���Ŏ擾�B
		glfwSetScrollCallback(window, InputMouseWheel);
	}

	void Input::BeginFrame()
	{
		//�|�[�����O�������g���}�E�X����Ȃǂ̃C�x���g���擾����B
		glfwPollEvents();
	}

	void Input::Update()
	{
		auto window = GraphicsEngine::GetInstance()->GetWindow();

		InputKey(window);

		InputMouseCursor(window);

		InputMouseButton(window);
	}

	void Input::EndFrame()
	{
		m_mouseWheel = 0.0f;
	}

	/// <summary>
	/// �L�[�̓��͏����B
	/// </summary>
	void Input::InputKey(GLFWwindow* window)
	{
		int keyNum = 0;
		int bitArray = 0;

		for (const VirtualPadToKeyPad& keyPad : keyPadTable) {

			keyNum = keyPad.keyCode % BIT_NUM_MAX;
			bitArray = keyPad.keyCode / BIT_NUM_MAX;

			//�L�[��������Ă�����B
			if (glfwGetKey(window, keyPad.keyNumber) == GLFW_PRESS) {

				if (m_keyPressBit[bitArray].IsSetFlag(keyNum)) {
					m_keyTriggerBit[bitArray].FoldFlag(keyNum);
				}
				else {
					m_keyTriggerBit[bitArray].SetFlag(keyNum);
				}
				m_keyPressBit[bitArray].SetFlag(keyNum);
				m_keyReleaseBit[bitArray].FoldFlag(keyNum);
			}
			//������Ă��Ȃ��Ȃ�B
			else {

				if (m_keyPressBit[bitArray].IsSetFlag(keyNum)) {
					m_keyReleaseBit[bitArray].SetFlag(keyNum);
				}
				else {
					m_keyReleaseBit[bitArray].FoldFlag(keyNum);
				}
				m_keyTriggerBit[bitArray].FoldFlag(keyNum);
				m_keyPressBit[bitArray].FoldFlag(keyNum);
			}
		}
	}
	
	/// <summary>
	/// �}�E�X�̓��͏����B
	/// </summary>
	void Input::InputMouseCursor(GLFWwindow* window)
	{
		//�E�B���h�E�T�C�Y���擾�B
		Vector2 windowSize;
		windowSize = GraphicsEngine::GetInstance()->GetWindowSize();

		//�}�E�X�̍��W���擾�B
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//��ʂ͈͓̔��Ƀ}�E�X������Ȃ�B
		if (mouseX > 0.0f &&
			mouseX < windowSize.x &&
			mouseY > 0.0f &&
			mouseY < windowSize.y
			) {

			m_mouseAxis = m_mousePosition;

			//���W��ۑ�����B
			m_mousePosition.x = static_cast<float>(mouseX);
			m_mousePosition.y = static_cast<float>(mouseY);

			//���W�̓��͗ʂ��v�Z�B
			m_mouseAxis -= m_mousePosition;
			m_mouseAxis.Normalize();
			m_mouseAxis.Scale(-1.0f);
		}
		else {
			m_mouseAxis = Vector2::Zero;
		}

		//�J�[�\�����Œ�Ȃ�A���W��ݒ�B
		if (m_cursorLock) {
			windowSize.Div(2.0f);
			//�J�[�\���̈ʒu���Œ�B
			glfwSetCursorPos(window, windowSize.x, windowSize.y);
			m_mousePosition.Set(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
		}
	}

	/// <summary>
	/// �}�E�X�{�^���̓��́B
	/// </summary>
	void Input::InputMouseButton(GLFWwindow* window)
	{
		for (const VirtualPadToMouseButton& mouseButton : mouseButtonTable) {
			//�}�E�X�{�^����������Ă�����B
			if (glfwGetMouseButton(window, mouseButton.MouseNumber) == GLFW_PRESS) {
				m_mouseTrigger[mouseButton.mouseButton] = 1 ^ m_mousePress[mouseButton.mouseButton];
				m_mousePress[mouseButton.mouseButton] = true;
			}
			//�}�E�X�{�^����������Ă��Ȃ��Ȃ�B
			else {
				m_mouseRelease[mouseButton.mouseButton] = m_mousePress[mouseButton.mouseButton];
				m_mousePress[mouseButton.mouseButton] = false;
			}
		}
	}
}