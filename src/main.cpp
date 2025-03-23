#include "Plane.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "settings.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>
#include <iostream>

#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <vector>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

void initScene(Scene &scene)
{
	/*
	Camera
	– Assume a perspective camera
	– eye point at e = (0, 0, 0)
	– orientation given by u = (1, 0, 0), v = (0, 1, 0) and w = (0, 0, 1).
	– (Note that the camera is looking along the direction −w.)
	– Assume that the viewing region on the image plane is defined by
		l = −0.1, r = 0.1, b = −0.1, t = 0.1, and d = 0.1.
	*/
	scene.setCameraImagePlane(-0.1, 0.1, -0.1, 0.1);
	scene.setCameraEye(glm::vec3(0, 0, 0));
	scene.setCameraDistance(0.1);
	scene.setCameraDirection(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0),
							 glm::vec3(0, 0, 1));

	/*
	 The scene consists of the following four objects:
	 – Plane P , with equation y = −2.
	 – Sphere S1, with center at (−4, 0, −7) and radius 1.
	 – Sphere S2, with center at (0, 0, −7) and radius 2.
	 – Sphere S3, with center at (4, 0, −7) and radius 1.
	*/
	scene.addSurface(Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0)));
	scene.addSurface(Sphere(glm::vec3(-4, 0, -7), 1));
	scene.addSurface(Sphere(glm::vec3(0, 0, -7), 2));
	scene.addSurface(Sphere(glm::vec3(4, 0, -7), 1));
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
						int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void initGLFW(GLFWwindow **window)
{
	if (!glfwInit())
		return;

	// use openGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// create window and use
	*window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
							   "Ray-Tracer (Assignment 1)", NULL, NULL);
	if (!*window)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(*window);
	glfwSetKeyCallback(*window, keyCallback);
}

void renderFrameLoop(Renderer &renderer, GLFWwindow *window)
{
	bool needRecompute = true;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if (needRecompute)
		{
			renderer.rayTrace();
			needRecompute = false;
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderer.textureID);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
int main()
{
	Renderer    renderer;
	GLFWwindow *window;

	initScene(renderer.scene);
	initGLFW(&window);
	if (window == NULL)
		return (1);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// loop
	renderFrameLoop(renderer, window);

	// terminate
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
