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
		constexpr static float DegToRad(const float deg)
		{
			return deg * (PI / 180.0f);
		}

		/// <summary>
		/// Radian単位からDegree単位に変換。
		/// </summary>
		/// <param name="rad"></param>
		/// <returns></returns>
		constexpr static float RadToDeg(const float rad)
		{
			return rad / (PI / 180.0f);
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
	};
}