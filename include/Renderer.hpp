#ifndef RENDERER_HPP
#define RENDERER_HPP

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#endif

#include "Scene.hpp"
#include "settings.h"

class Renderer
{
  private:
  public:
	Scene         scene;
	unsigned char output[SCR_WIDTH * SCR_HEIGHT * 3]; // RGB
	GLuint        textureID;

	Renderer();
	~Renderer();
	void rayTrace();
};

#endif
