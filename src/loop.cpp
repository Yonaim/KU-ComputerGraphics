#include "gl_core.h"
#include "Renderer.hpp"

static void computeRayTracing(Renderer &renderer)
{
	std::cout << "Starting ray tracing..." << std::endl;
	renderer.rayTrace();
	std::cout << "Ray tracing complete!" << std::endl;
}

static void flipImageVertically(std::vector<unsigned char> &image, int width,
								int height)
{
	int                        rowSize = width * 3; // RGB
	std::vector<unsigned char> temp(rowSize);

	for (int y = 0; y < height / 2; ++y)
	{
		int topIndex    = y * rowSize;
		int bottomIndex = (height - 1 - y) * rowSize;

		std::memcpy(temp.data(), &image[topIndex], rowSize);
		std::memcpy(&image[topIndex], &image[bottomIndex], rowSize);
		std::memcpy(&image[bottomIndex], temp.data(), rowSize);
	}
}

void renderFrameLoop(Renderer &renderer, GLFWwindow *window)
{
	bool needRecompute = true;

	srand(time(NULL));
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(SCR_WIDTH, SCR_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE,
					 &renderer.output[0]);

		if (needRecompute)
		{
			computeRayTracing(renderer);
			flipImageVertically(renderer.output, SCR_WIDTH, SCR_HEIGHT);
			needRecompute = false;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
