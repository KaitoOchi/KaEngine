#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �����_�����O�R���e�L�X�g�B
	/// </summary>
	class RenderContext : Noncopyable
	{
	public:

		/// <summary>
		/// �����_�[�^�[�Q�b�g�̃N���A�B
		/// </summary>
		void ClearRenderTarget()
		{
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
	};
}
