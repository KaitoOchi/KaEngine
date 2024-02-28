#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ゲームオブジェクト。
	/// </summary>
	class GameObject : Noncopyable
	{
	public:
		virtual ~GameObject() {}

		/// <summary>
		/// Start関数。
		/// </summary>
		/// <returns>trueなら次フレームからUpdate関数が呼ばれます</returns>
		virtual bool Start()
		{
			return true;
		}

		/// <summary>
		/// Update関数。
		/// </summary>
		virtual void Update()
		{

		}

		/// <summary>
		/// Render関数。
		/// </summary>
		virtual void Render()
		{

		}

	public:
		/// <summary>
		/// 名前を設定。
		/// </summary>
		/// <param name="name"></param>
		void SetName(const char* name)
		{
			m_objectName = name;
		}

		/// <summary>
		/// 名前が一致するかどうか。
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		const bool IsMatchName(const char* name) const
		{
			if (m_isActive) {
				if (strcmp(m_objectName.c_str(), name) == 0) {
					return true;
				}
			}
			return false;
		}

		/// <summary>
		/// 有効化。
		/// </summary>
		void Activate()
		{
			m_isActive = true;
		}

		/// <summary>
		/// 無効化。
		/// </summary>
		void Deactivate()
		{
			m_isActive = false;
		}

		/// <summary>
		/// 有効化状態の切り替え。
		/// </summary>
		void ToggleActivate()
		{
			m_isActive = !m_isActive;
		}

		/// <summary>
		/// アクティブ状態かどうか。
		/// </summary>
		const bool IsActive() const
		{
			return m_isActive;
		}

	public:
		/// <summary>
		/// 破棄する。
		/// </summary>
		void Destroy()
		{
			m_isDestroy = true;
		}

		/// <summary>
		/// 破棄するかどうか。
		/// </summary>
		/// <returns></returns>
		const bool IsDestroy() const
		{
			return m_isDestroy;
		}

		void StartWrapper()
		{
			if (!m_isStart && !m_isDestroy && m_isActive) {
				if (Start() == true) {
					m_isStart = true;
				}
			}
		}

		void UpdateWrapper()
		{
			if (m_isStart && !m_isDestroy && m_isActive) {
				Update();
			}
		}

		void RenderWrapper()
		{
			if (m_isStart && m_isDestroy && m_isActive) {
				Render();
			}
		}

	protected:
		std::string m_objectName = "default";	//オブジェクト名。
		bool m_isStart = false;					//Start関数が終了したかどうか。
		bool m_isDestroy = false;				//破棄したかどうか。
		bool m_isActive = true;					//有効状態かどうか。
	};
}


