#include "gl_core.h"
#include "settings.h"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

static void print_resolution(GLFWwindow *window)
{
	int windowWidth, windowHeight;

	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	std::cout << "Window Size: " << windowWidth << "x" << windowHeight
			  << std::endl;

	int framebufferWidth, framebufferHeight;
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	std::cout << "Framebuffer Size: " << framebufferWidth << "x"
			  << framebufferHeight << std::endl;

	float pixelRatioX = (float)framebufferWidth / windowWidth;
	float pixelRatioY = (float)framebufferHeight / windowHeight;
	std::cout << "Pixel Ratio: " << pixelRatioX << "x" << pixelRatioY
			  << std::endl;
}

static void print_version()
{
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
			  << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

void init_camera(Camera &camera)
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
	camera.setEye(glm::vec3(0, 0, 0));
	camera.setDirection(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0),
						glm::vec3(0, 0, 1));
	camera.setDistance(0.1f);
	camera.setImagePlane(-0.1f, 0.1f, -0.1f, 0.1f);
}

void init_surfaces(std::vector<Surface *> &surfaces)
{
	/*
	Use the Phong model to shade the scene, with the following material
	parameters for each object:
	– Plane P : ka = (0.2, 0.2, 0.2), kd = (1, 1, 1), ks = (0, 0, 0), with
		specular power 0.
	– Sphere S1 : ka = (0.2, 0, 0), kd = (1, 0, 0), ks = (0,
		0, 0), with specular power 0
	– Sphere S2 : ka = (0, 0.2, 0), kd = (0, 0.5,
		0), ks = (0.5, 0.5, 0.5), with specular power 32.
	– Sphere S3 : ka = (0, 0,
		0.2), kd = (0, 0, 1), ks = (0, 0, 0), with specular power 0.
	*/
	Material *m_p  = new Material(glm::vec3(0.2, 0.2, 0.2), glm::vec3(1, 1, 1),
								  glm::vec3(0, 0, 0), 0);
	Material *m_s1 = new Material(glm::vec3(0.2, 0, 0), glm::vec3(1, 0, 0),
								  glm::vec3(0, 0, 0), 0);
	Material *m_s2 = new Material(glm::vec3(0, 0.2, 0), glm::vec3(0, 0.5, 0),
								  glm::vec3(0.5, 0.5, 0.5), 32);
	Material *m_s3 = new Material(glm::vec3(0, 0, 0.2), glm::vec3(0, 0, 1),
								  glm::vec3(0, 0, 0), 0);

	Plane  *plane   = new Plane(glm::vec3(0, -2, 0), m_p, glm::vec3(0, 1, 0));
	Sphere *sphere1 = new Sphere(glm::vec3(-4, 0, -7), m_s1, 1);
	Sphere *sphere2 = new Sphere(glm::vec3(0, 0, -7), m_s2, 2);
	Sphere *sphere3 = new Sphere(glm::vec3(4, 0, -7), m_s3, 1);

	/*
	The scene consists of the following four objects:
	– Plane P , with equation y = −2.
	– Sphere S1, with center at (−4, 0, −7) and radius 1.
	– Sphere S2, with center at (0, 0, −7) and radius 2.
	– Sphere S3, with center at (4, 0, −7) and radius 1.
	*/
	surfaces.push_back(plane);
	surfaces.push_back(sphere1);
	surfaces.push_back(sphere2);
	surfaces.push_back(sphere3);
}

void init_point_lights(std::vector<PointLight *> &lights)
{
	/*
	Assume a single point light source at (−4, 4, −3), emitting white light with
	unit intensity and no falloff.
	*/
	PointLight *light
		= new PointLight(glm::vec3(-4, 4, -3), glm::vec3(1, 1, 1), 1);
	lights.push_back(light);
}

void init_scene(Scene &scene)
{
	init_camera(scene.getCamera());
	init_surfaces(scene.getSurfaces());
	init_point_lights(scene.getLights());
	scene.setBackgroundColor(glm::vec3(0, 0, 0));
}

GLFWwindow *init_glfw()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return (NULL);
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// ignore DPI scaling (1:1 mapping)
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif

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
	// print_resolution(window);

	return (window);
}
