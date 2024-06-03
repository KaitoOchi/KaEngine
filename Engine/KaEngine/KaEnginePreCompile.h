#pragma once

// C++
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <list>
#include <memory>
#include <functional>

#ifdef _WIN32

#include <Windows.h>

#endif

// openGL
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

// bulletphysics
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"


const float FRAME_BUFFER_WIDTH = 1600.0f;
const float FRAME_BUFFER_HEIGHT = 900.0f;

// system
#include "../Game/system.h"

// util
#include "util/Noncopyable.h"
#include "util/TResourceBank.h"

// debug
#include "dbg/KaDebug.h"

// math
#include "math/Mathf.h"
#include "math/Vector.h"
#include "math/Matrix.h"
#include "math/BitFlag.h"
#include "math/Transform.h"

// Graphics
#include "graphics/VBO.h"
#include "graphics/VAO.h"
#include "graphics/EBO.h"
#include "graphics/ShaderClass.h"
#include "graphics/Texture.h"
#include "graphics/RenderTarget.h"
#include "graphics/UniformBuffer.h"
#include "graphics/RenderContext.h"
#include "graphics/Mesh.h"
#include "graphics/Sprite.h"
#include "graphics/Material.h"
#include "graphics/GraphicsEngine.h"

// physics
#include "dbg/DebugWireFrame.h"
#include "physics/ICollider.h"
#include "physics/BoxCollider.h"
#include "physics/CapsuleCollider.h"
#include "physics/SphereCollider.h"
#include "physics/PhysicsEngine.h"
#include "physics/PhysicsGhostObject.h"
#include "physics/Rigidbody.h"

// Time
#include "timer/Timer.h"
#include "timer/GameTime.h"

// Camera
#include "Camera.h"

// HID
#include "HID/Input.h"

// GameObject
#include "gameObject/GameObject.h"
#include "gameObject/GameObjectManager.h"

#include "KaEngine.h"