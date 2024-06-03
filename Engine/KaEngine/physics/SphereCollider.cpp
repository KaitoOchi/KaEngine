#include "KaEnginePreCompile.h"
#include "SphereCollider.h"

namespace nsKaEngine {

	void SphereCollider::Create(const float radius)
	{
		m_shape = std::make_unique<btSphereShape>(radius);
		m_radius = radius;
	}
}