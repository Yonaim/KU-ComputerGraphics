#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "graphics.h"

class Renderer
{
  private:
	/* data */
  public:
	Scene         scene;
	unsigned char output[SCR_WIDTH * SCR_HEIGHT * 3]; // RGB
	GLuint        textureID;

	Renderer();
	~Renderer();
	void rayTrace();
};

#endif
