#include "KaEnginePreCompile.h"
#include "BoxCollider.h"

namespace nsKaEngine {

	void BoxCollider::Create(const Vector3& size)
	{
		m_shape = std::make_unique<btBoxShape>(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
		m_size = size;
	}
}