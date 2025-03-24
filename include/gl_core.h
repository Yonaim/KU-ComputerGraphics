#ifndef GL_CORE_H
#define GL_CORE_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/dual_quaternion.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <Windows.h>
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#else
#include <GL/GL.h>
#include <GL/freeglut.h>
#endif

#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <vector>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#endif
