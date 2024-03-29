#pragma once

namespace nsKaEngine {

	class Mathf
	{
	public:
		static constexpr float PI = 3.14159265358979323846f;	//円周率。
		static constexpr float PI2 = PI * 2.0f;					//円周率の2乗。

		/// <summary>
		/// Degree単位からRadian単位に変換。
		/// </summary>
		/// <param name="deg"></param>
		/// <returns></returns>
		const static float DegToRad(const float deg)
		{
			return glm::radians(deg);
		}

		/// <summary>
		/// Radian単位からDegree単位に変換。
		/// </summary>
		/// <param name="rad"></param>
		/// <returns></returns>
		const static float RadToDeg(const float rad)
		{
			return glm::degrees(rad);
		}

		/// <summary>
		/// 少数を四捨五入。
		/// </summary>
		/// <param name="round"></param>
		/// <returns></returns>
		const static float Round(const float round)
		{
			return glm::round(round);
		}

		/// <summary>
		/// 少数を整数に切り捨て。
		/// </summary>
		/// <param name="floor"></param>
		/// <returns></returns>
		const static float Floor(const float floor)
		{
			return glm::floor(floor);
		}

		/// <summary>
		/// 少数を整数を切り上げ。
		/// </summary>
		/// <param name="ceil"></param>
		/// <returns></returns>
		const static float Ceil(const float ceil)
		{
			return glm::ceil(ceil);
		}

		/// <summary>
		/// 最小から最大の間で値を収める。
		/// </summary>
		/// <param name="clamp"></param>
		/// <returns></returns>
		const static float Clamp(const float clamp, const float min, const float max)
		{
			return glm::clamp(clamp, min, max);
		}

		/// <summary>
		/// 値の正負を取得。
		/// </summary>
		/// <param name="sign"></param>
		/// <returns></returns>
		const static float Sign(const float sign)
		{
			return glm::sign(sign);
		}

		/// <summary>
		/// 仮数を取得。
		/// </summary>
		/// <param name="fract"></param>
		/// <returns></returns>
		const static float Fract(const float fract)
		{
			return glm::fract(fract);
		}

		/// <summary>
		/// 線形補間。
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
