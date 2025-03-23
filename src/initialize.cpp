#include "graphics.hpp"

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

GLFWwindow *init_glfw()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(
		GLFW_OPENGL_FORWARD_COMPAT,
		GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	// glfw window creation
	GLFWwindow *window
		= glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ray-Tracer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

bool init_glad()
{
	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}
