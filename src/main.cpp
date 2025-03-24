#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/dual_quaternion.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <Windows.h>
#include <GL/glew.h>
#endif

#include <iostream>

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

#include "settings.h"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

void errorCallback(int error, const char *description)
{
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

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
	scene.addSurface(new Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0)));
	scene.addSurface(new Sphere(glm::vec3(-4, 0, -7), 1));
	scene.addSurface(new Sphere(glm::vec3(0, 0, -7), 2));
	scene.addSurface(new Sphere(glm::vec3(4, 0, -7), 1));
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
						int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

GLFWwindow *initGLFW()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// Try with a compatibility profile first
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Create window and use
	GLFWwindow *window = glfwCreateWindow(
		SCR_WIDTH, SCR_HEIGHT, "Ray-Tracer (Assignment 1)", NULL, NULL);

	if (!window)
	{
		std::cout << "Window creation failed, trying alternative settings"
				  << std::endl;
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
								  "Ray-Tracer (Assignment 1)", NULL, NULL);

		if (!window)
		{
			std::cout << "Window creation failed again" << std::endl;
			glfwTerminate();
			return NULL;
		}
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
		return NULL;
	}
#endif

	// Print OpenGL version info
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
			  << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	return window;
}

void renderFrameLoop(Renderer &renderer, GLFWwindow *window)
{
	bool needRecompute = true;

	while (!glfwWindowShouldClose(window))
	{
		// 화면 클리어
		glClear(GL_COLOR_BUFFER_BIT);

		// 레이트레이싱 실행
		if (needRecompute)
		{
			std::cout << "Starting ray tracing..." << std::endl;
			renderer.rayTrace();
			needRecompute = false;
			std::cout << "Ray tracing complete!" << std::endl;

			// 텍스처 업데이트
			glBindTexture(GL_TEXTURE_2D, renderer.textureID);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCR_WIDTH, SCR_HEIGHT,
							GL_RGB, GL_UNSIGNED_BYTE, renderer.output);
		}

		// 텍스처 바인딩
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderer.textureID);

		// 전체 화면 쿼드 그리기
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

		// 오류 체크
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL error in render loop: " << error << std::endl;
		}

		// 버퍼 스왑 및 이벤트 폴링
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	Renderer    renderer;
	GLFWwindow *window = NULL;

	glfwSetErrorCallback(errorCallback);

	initScene(renderer.scene);

	window = initGLFW();
	if (window == NULL)
		return (1);

	renderer.setupTexture();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// 렌더링 루프 시작
	renderFrameLoop(renderer, window);

	// 종료
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
