#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Scene.hpp"
#include "settings.h"
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

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
