#include "KaEnginePreCompile.h"
#include "Vector.h"

namespace nsKaEngine {

	const Vector2 Vector2::Zero = { 0.0f, 0.0f };
	const Vector2 Vector2::One = { 1.0f, 1.0f };
	const Vector2 Vector2::DEFAULT_PIVOT = { 0.5f, 0.5f };

	const Vector3 Vector3::Zero = { 0.0f, 0.0f, 0.0f };
	const Vector3 Vector3::One = { 1.0f, 1.0f, 1.0f };
	const Vector3 Vector3::Up = { 0.0f, 1.0f, 0.0f };
	const Vector3 Vector3::Forward = { 0.0f, 0.0f, 1.0f };
	const Vector3 Vector3::Backward = { 0.0f, 0.0f, -1.0f };

	const Vector4 Vector4::White = { 1.0f, 1.0f, 1.0f, 1.0f };
	const Vector4 Vector4::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	const Vector4 Vector4::Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	const Vector4 Vector4::Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	const Vector4 Vector4::Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	const Vector4 Vector4::Gray = { 0.5f, 0.5f, 0.5f, 1.0f };

	const Quaternion Quaternion::Identity = { 0.0f, 0.0f, 0.0f, 1.0f };
}