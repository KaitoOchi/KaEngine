#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �r���[�|�[�g�B
	/// </summary>
	struct VIEWPORT
	{
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
	};

	/// <summary>
	/// �����_�����O�R���e�L�X�g�B
	/// </summary>
	class RenderContext : Noncopyable
	{
	public:

		/// <summary>
		/// �����_�[�^�[�Q�b�g�̃N���A�B
		/// </summary>
		void ClearRenderTarget(RenderTarget& rt)
		{
			Vector4 clearColor = rt.GetClearColor();
			glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		/// <summary>
		/// �����_�[�^�[�Q�b�g�̐ڑ��B
		/// </summary>
		/// <param name="rt"></param>
		void BindRenderTarget(RenderTarget& rt)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, rt.GetID());
		}

		/// <summary>
		/// �����_�[�^�[�Q�b�g�ƃr���[�|�[�g�̐ݒ�B
		/// </summary>
		/// <param name="rt"></param>
		void BindRenderTargetAndViewport(RenderTarget& rt)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, rt.GetID());
			SetViewportAndScissor(rt.GetWidth(), rt.GetHeight());
		}

		/// <summary>
		/// �����_�[�^�[�Q�b�g�̐ڑ��������B
		/// </summary>
		void UnBindRenderTarget()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		/// <summary>
		/// �r���[�|�[�g�ƃV�U�����O��`��ݒ�B
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetViewportAndScissor(const int width, const int height)
		{
			SetViewport(0, 0, width, height);
			SetScissor(0, 0, width, height);
		}

		/// <summary>
		/// �r���[�|�[�g��ݒ�B
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetViewport(
			const int x,
			const int y,
			const int width,
			const int height
		) {
			glViewport(x, y, width, height);
			m_viewport.x = x;
			m_viewport.y = y;
			m_viewport.width = width;
			m_viewport.height = height;
		}

		/// <summary>
		/// �r���[�|�[�g���擾�B
		/// </summary>
		/// <returns></returns>
		const VIEWPORT& GetViewport() const
		{
			return m_viewport;
		}

		/// <summary>
		/// �V�U�����O��`��ݒ�B
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetScissor(
			const int x,
			const int y,
			const int width,
			const int height
		) {
			glScissor(x, y, width, height);
		}

	private:
		VIEWPORT m_viewport;		//�r���[�|�[�g�B
	};
}