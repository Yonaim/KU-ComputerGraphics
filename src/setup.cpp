#include "gl_core.h"
#include "settings.h"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

static void print_version()
{
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
			  << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

void init_scene(Scene &scene)
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
	scene.setCameraImagePlane(-0.1f, 0.1f, -0.1f, 0.1f);
	scene.setCameraEye(glm::vec3(0, 0, 0));
	scene.setCameraDistance(0.1f);
	scene.setCameraDirection(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0),
							 glm::vec3(0, 0, 1));

	/*
	 The scene consists of the following four objects:
	 – Plane P , with equation y = −2.
	 – Sphere S1, with center at (−4, 0, −7) and radius 1.
	 – Sphere S2, with center at (0, 0, −7) and radius 2.
	 – Sphere S3, with center at (4, 0, −7) and radius 1.
	*/
	scene.addSurface(new Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0)));
	scene.addSurface(new Sphere(glm::vec3(-4, 0, -7), 1));
	scene.addSurface(new Sphere(glm::vec3(0, 0, -7), 2));
	scene.addSurface(new Sphere(glm::vec3(4, 0, -7), 1));
}

GLFWwindow *init_glfw()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return (NULL);
	}

	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Create window and use
	GLFWwindow *window = glfwCreateWindow(
		SCR_WIDTH, SCR_HEIGHT, "Ray-Tracer (Assignment 1)", NULL, NULL);

	if (!window)
	{
		std::cout << "Window creation failed" << std::endl;
		glfwTerminate();
		return (NULL);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

#ifndef __APPLE__
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err)
				  << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return (NULL);
	}
#endif

	print_version();

	return (window);
}
