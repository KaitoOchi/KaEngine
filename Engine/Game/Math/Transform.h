#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ���W�A��]�A�g��N���X�B
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