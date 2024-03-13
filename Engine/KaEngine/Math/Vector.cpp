#include "KaEnginePreCompile.h"
#include "Vector.h"

namespace nsKaEngine {

	////////////////////////////////////////
	/// Vector2�̒萔
	////////////////////////////////////////
	const Vector2 Vector2::Zero = { 0.0f, 0.0f };
	const Vector2 Vector2::One = { 1.0f, 1.0f };

	const Vector2Int Vector2Int::Zero = { 0, 0 };
	const Vector2Int Vector2Int::One = { 1, 1};

	const Vector2Double Vector2Double::Zero = { 0.0, 0.0 };
	const Vector2Double Vector2Double::One = { 1.0, 1.0 };


	////////////////////////////////////////
	/// Vector3�̒萔
	////////////////////////////////////////
	const Vector3 Vector3::Zero = { 0.0f, 0.0f, 0.0f };
	const Vector3 Vector3::One = { 1.0f, 1.0f, 1.0f };
	const Vector3 Vector3::Up = { 0.0f, 1.0f, 0.0f };
	const Vector3 Vector3::Forward = { 0.0f, 0.0f, 1.0f };
	const Vector3 Vector3::Backward = { 0.0f, 0.0f, -1.0f };
	const Vector3 Vector3::AxisX = { 1.0f,  0.0f,  0.0f };
	const Vector3 Vector3::AxisY = { 0.0f,  1.0f,  0.0f };
	const Vector3 Vector3::AxisZ = { 0.0f,  0.0f,  1.0f };

	const Vector3Int Vector3Int::Zero = { 0, 0, 0 };
	const Vector3Int Vector3Int::One = { 1, 1, 1 };
	const Vector3Int Vector3Int::Up = { 0, 1, 0 };
	const Vector3Int Vector3Int::Forward = { 0, 0, 1 };
	const Vector3Int Vector3Int::Backward = { 0, 0, -1 };
	const Vector3Int Vector3Int::AxisX = { 1,  0,  0 };
	const Vector3Int Vector3Int::AxisY = { 0,  1,  0 };
	const Vector3Int Vector3Int::AxisZ = { 0,  0,  1 };

	const Vector3Double Vector3Double::Zero = { 0.0, 0.0, 0.0 };
	const Vector3Double Vector3Double::One = { 1.0, 1.0, 1.0 };
	const Vector3Double Vector3Double::Up = { 0.0, 1.0, 0.0 };
	const Vector3Double Vector3Double::Forward = { 0.0, 0.0, 1.0 };
	const Vector3Double Vector3Double::Backward = { 0.0, 0.0, -1.0 };
	const Vector3Double Vector3Double::AxisX = { 1.0,  0.0,  0.0 };
	const Vector3Double Vector3Double::AxisY = { 0.0,  1.0,  0.0 };
	const Vector3Double Vector3Double::AxisZ = { 0.0,  0.0,  1.0 };


	////////////////////////////////////////
	/// Vector4�̒萔
	////////////////////////////////////////
	const Vector4 Vector4::White = { 1.0f, 1.0f, 1.0f, 1.0f };
	const Vector4 Vector4::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	const Vector4 Vector4::Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	const Vector4 Vector4::Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	const Vector4 Vector4::Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	const Vector4 Vector4::Gray = { 0.5f, 0.5f, 0.5f, 1.0f };

	const Quaternion Quaternion::Identity = { 0.0f, 0.0f, 0.0f, 1.0f };
}