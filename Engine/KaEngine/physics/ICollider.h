#pragma once

namespace nsKaEngine {

	class ICollider : Noncopyable
	{
	public:
		ICollider() {}
		~ICollider() {}

		virtual btCollisionShape* GetShape() const = 0;
	};
}

