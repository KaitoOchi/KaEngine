#pragma once

namespace nsKaEngine {

	/// <summary>
	/// 座標、回転、拡大クラス。
	/// </summary>
	class Transform : Noncopyable
	{
	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3::One;

		Vector3 forward;
		Vector3 up;
	};


}