#pragma once

namespace nsKaEngine {

	class GameObject : Noncopyable
	{
	public:
		virtual ~GameObject() {}

		/// <summary>
		/// Start�֐��B
		/// </summary>
		/// <returns>true�Ȃ玟�t���[������Update�֐����Ă΂�܂�</returns>
		virtual bool Start()
		{
			return true;
		}

		/// <summary>
		/// Update�֐��B
		/// </summary>
		virtual void Update()
		{

		}

		/// <summary>
		/// Render�֐��B
		/// </summary>
		virtual void Render()
		{

		}

	public:
		/// <summary>
		/// ���O��ݒ�B
		/// </summary>
		/// <param name="name"></param>
		void SetName(const char* name)
		{
			m_objectName = name;
		}

		/// <summary>
		/// �L�����B
		/// </summary>
		void Activate()
		{
			m_isActive = true;
		}

		/// <summary>
		/// �������B
		/// </summary>
		void Deactivate()
		{
			m_isActive = false;
		}

	public:
		/// <summary>
		/// �j������B
		/// </summary>
		void Destroy()
		{
			m_isDestroy = true;
		}

		/// <summary>
		/// �j�����邩�ǂ����B
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
		std::string m_objectName = "default";	//�I�u�W�F�N�g���B
		bool m_isStart = false;					//Start�֐����I���������ǂ����B
		bool m_isDestroy = false;				//�j���������ǂ����B
		bool m_isActive = true;					//�L����Ԃ��ǂ����B
	};
}

