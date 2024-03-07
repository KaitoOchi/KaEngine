#pragma once

// C++
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <list>

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
#include "graphics/UniformBuffer.h"
#include "graphics/Mesh.h"
#include "graphics/Sprite.h"
#include "graphics/RenderTarget.h"
#include "graphics/GraphicsEngine.h"
#include "graphics/Material.h"

// Time
#include "timer/Timer.h"
#include "timer/GameTime.h"

// Camera
#include "Camera.h"

// Input
#include "Input.h"

// GameObject
#include "gameObject/GameObject.h"
#include "gameObject/GameObjectManager.h"

#include "KaEngine.h"