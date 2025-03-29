#include <iostream>
#include "gl_core.h"
#include "settings.h"
#include "Renderer.hpp"

void        renderFrameLoop(Renderer &renderer, GLFWwindow *window);
void        init_scene(Scene &scene);
GLFWwindow *init_glfw();

// todo: 메모리 회수 작업
int main()
{
	Renderer    renderer;
	GLFWwindow *window = NULL;

	// set up
	glfwSetErrorCallback(errorCallback);
	init_scene(renderer.scene);
	window = init_glfw();
	if (window == NULL)
		return (1);

	// loop
	renderFrameLoop(renderer, window);

	// terminate
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
