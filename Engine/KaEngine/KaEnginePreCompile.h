#pragma once

// C++
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <Windows.h>

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

// Transform
#include "math/Transform.h"

#include "graphics/Material.h"
#include "graphics/Mesh.h"

// Time
#include "timer/FPSLimiter.h"

// Camera
#include "Camera.h"

// Input
#include "Input.h"

#include "KaEngine.h"