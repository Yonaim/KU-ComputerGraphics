#include "gl_core.h"
#include "Renderer.hpp"

static void clearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT); // can be added another code later
}

static void computeRayTracing(Renderer &renderer)
{
	std::cout << "Starting ray tracing..." << std::endl;
	renderer.rayTrace();
	std::cout << "Ray tracing complete!" << std::endl;

	glBindTexture(GL_TEXTURE_2D, renderer.textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RGB,
					GL_UNSIGNED_BYTE, renderer.output);
}

static void renderQuad(GLuint textureID)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void renderFrameLoop(Renderer &renderer, GLFWwindow *window)
{
	bool needRecompute = true;

	while (!glfwWindowShouldClose(window))
	{
		clearFrame();

		if (needRecompute)
		{
			computeRayTracing(renderer);
			needRecompute = false;
		}

		renderQuad(renderer.textureID);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL error in render loop: " << error << std::endl;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
