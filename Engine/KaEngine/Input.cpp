#include "KaEnginePreCompile.h"
#include "Input.h"

namespace nsKaEngine {

	Input* Input::m_instance = nullptr;

	namespace
	{
		struct VirtualPadToKeyPad {
			KeyCode		keyCode;		//キーコード。
			int			keyNumber;		//glfwのキー番号。
		};

		const VirtualPadToKeyPad keyPadTable[enButtonNum] = {
			{ enButtonW, GLFW_KEY_W },
			{ enButtonA, GLFW_KEY_A },
			{ enButtonS, GLFW_KEY_S },
			{ enButtonD, GLFW_KEY_D },
		};
	}

	Input::Input()
	{
		memset(m_trigger, 0, sizeof(m_trigger));
		memset(m_press, 0, sizeof(m_press));
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
	/// キーの入力処理。
	/// </summary>
	void Input::InputKey()
	{
		for (const VirtualPadToKeyPad& keyPad : keyPadTable) {

			if (glfwGetKey(m_window, keyPad.keyNumber) == GLFW_PRESS) {
				m_press[keyPad.keyCode] = true;
			}
			else {
				m_press[keyPad.keyCode] = false;
			}
		}
	}
	
	/// <summary>
	/// マウスの入力処理。
	/// </summary>
	void Input::InputMouse()
	{
		double mouseX, mouseY;
		glfwGetCursorPos(m_window, &mouseX, &mouseY);

		m_mouseAxis = m_mousePosition;

		//画面の範囲内にマウスがあるなら。
		if (mouseX > 0.0f &&
			mouseX < 1600.0f &&
			mouseY > 0.0f &&
			mouseY < 900.0f
		) {
			//座標を保存する。
			m_mousePosition.x = mouseX;
			m_mousePosition.y = mouseY;
			
			//座標の入力量を計算。
			m_mouseAxis -= m_mousePosition;
			m_mouseAxis.Normalize();
		}
		else {
			m_mouseAxis = Vector3::Zero;
		}

		//if (isnan(m_mouseAxis.x)) {
		//	m_mouseAxis = Vector3::Zero;
		//}
	}
}