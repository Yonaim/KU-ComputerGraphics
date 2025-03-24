#include <iostream>
#include "gl_core.h"

void errorCallback(int error, const char *description)
{
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
				 int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void resizeCallback(GLFWwindow *window, int width, int height)
{
	// no action
}
