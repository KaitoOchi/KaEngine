#include "KaEnginePreCompile.h"
#include "CapsuleCollider.h"

namespace nsKaEngine {

	void CapsuleCollider::Create(const float radius, const float height)
	{
		m_shape = std::make_unique<btCapsuleShape>(radius, height);
		m_radius = radius;
		m_height = height;
	}
}