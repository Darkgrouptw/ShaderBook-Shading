#pragma once

#ifdef _MSC_VER
    #include "GLEW/glew.h"
    #include "FreeGLUT/freeglut.h"
#include <direct.h>
#else
    #include <OpenGL/gl3.h>
    #include <GLUT/glut.h>
    #include <unistd.h>
#endif
#include "../Include/AntTweakBar.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../Include/TinyOBJ/tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Include/STB/stb_image.h"

#ifdef _MSC_VER
    #pragma comment (lib, "glew32.lib")
	#pragma comment(lib, "freeglut.lib")
#endif

#define GLM_SWIZZLE
#include "GLM/glm/glm.hpp"
#include "GLM/glm/gtc/matrix_transform.hpp"
#include "GLM/glm/gtc/type_ptr.hpp"
#include "GLM/glm/gtx/rotate_vector.hpp"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>

#ifdef _MSC_VER
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
    #define __FILEPATH__(x) ((std::string(__FILE__).substr(0, std::string(__FILE__).rfind('\\'))+(x)).c_str())
#else
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #define __FILEPATH__(x) ((std::string(__FILE__).substr(0, std::string(__FILE__).rfind('/'))+(x)).c_str())
#endif

#define deg2rad(x) ((x)*((3.1415926f)/(180.0f)))
#define rad2deg(x) ((180.0f) / ((x)*(3.1415926f)))