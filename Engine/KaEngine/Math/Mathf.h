#pragma once

namespace nsKaEngine {

	class Mathf
	{
	public:
		static constexpr float PI = 3.14159265358979323846f;	//�~�����B
		static constexpr float PI2 = PI * 2.0f;					//�~������2��B

		/// <summary>
		/// Degree�P�ʂ���Radian�P�ʂɕϊ��B
		/// </summary>
		/// <param name="deg"></param>
		/// <returns></returns>
		constexpr static float DegToRad(const float deg)
		{
			return deg * (PI / 180.0f);
		}

		/// <summary>
		/// Radian�P�ʂ���Degree�P�ʂɕϊ��B
		/// </summary>
		/// <param name="rad"></param>
		/// <returns></returns>
		constexpr static float RadToDeg(const float rad)
		{
			return rad / (PI / 180.0f);
		}

		/// <summary>
		/// �ŏ�����ő�̊ԂŒl�����߂�B
		/// </summary>
		/// <param name="clamp"></param>
		/// <returns></returns>
		const static float Clamp(const float clamp, const float min, const float max)
		{
			return glm::clamp(clamp, min, max);
		}

		/// <summary>
		/// �l�̐������擾�B
		/// </summary>
		/// <param name="sign"></param>
		/// <returns></returns>
		const static float Sign(const float sign)
		{
			return glm::sign(sign);
		}
	};
}