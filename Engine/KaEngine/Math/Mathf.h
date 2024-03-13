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
		const static float DegToRad(const float deg)
		{
			return glm::radians(deg);
		}

		/// <summary>
		/// Radian�P�ʂ���Degree�P�ʂɕϊ��B
		/// </summary>
		/// <param name="rad"></param>
		/// <returns></returns>
		const static float RadToDeg(const float rad)
		{
			return glm::degrees(rad);
		}

		/// <summary>
		/// �������l�̌ܓ��B
		/// </summary>
		/// <param name="round"></param>
		/// <returns></returns>
		const static float Round(const float round)
		{
			return glm::round(round);
		}

		/// <summary>
		/// �����𐮐��ɐ؂�̂āB
		/// </summary>
		/// <param name="floor"></param>
		/// <returns></returns>
		const static float Floor(const float floor)
		{
			return glm::floor(floor);
		}

		/// <summary>
		/// �����𐮐���؂�グ�B
		/// </summary>
		/// <param name="ceil"></param>
		/// <returns></returns>
		const static float Ceil(const float ceil)
		{
			return glm::ceil(ceil);
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

		/// <summary>
		/// �������擾�B
		/// </summary>
		/// <param name="fract"></param>
		/// <returns></returns>
		const static float Fract(const float fract)
		{
			return glm::fract(fract);
		}

		/// <summary>
		/// ���`��ԁB
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <param name="time"></param>
		/// <returns></returns>
		const static float Lerp(const float a, const float b, const float time)
		{
			return glm::mix(a, b, time);
		}
	};
}
