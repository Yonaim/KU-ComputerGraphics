#include "Renderer.hpp"
#include "Scene.hpp"
#include "constant.h"
#include "settings.h"
#include <cstring>
#include "debug.h"

Renderer::Renderer()
{
	memset(output, 0, SCR_WIDTH * SCR_HEIGHT * 3);
	this->textureID = 0;
}

Renderer::~Renderer()
{
	glDeleteTextures(1, &textureID);
}

void Renderer::setupTexture()
{
	std::cout << "Setting up texture..." << std::endl;

	memset(output, 0, sizeof(output));

	glGenTextures(1, &textureID);
	std::cout << "Generated texture ID: " << textureID << std::endl;

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, output);

	std::cout << "Texture setup successful" << std::endl;
}

/*
– Write a ray tracer which generates eye rays through the center
of each pixel
– Calculates the intersection between each ray and each object in
the scene
– Also calculating the closest intersection (if any) for each ray.
– For each pixel, if the corresponding ray intersects an object, set
the pixel’s color to white; otherwise, set the pixel’s color to
black.
– See the Figure for a reference image.
*/
void Renderer::rayTrace()
{
	Camera   &camera = scene.getCamera();
	glm::vec3 color;
	Ray       ray;

	for (int y = 0; y < SCR_HEIGHT; y++)
	{
		std::cout << "Processing line number " << y + 1 << "..." <<
		std::endl;
		for (int x = 0; x < SCR_WIDTH; x++)
		{
			ray   = camera.getRay(x, y);
			color = scene.trace(ray, 0, FLT_INF);

			int idx         = (y * SCR_WIDTH + x) * 3;
			output[idx]     = (unsigned char)(color.x * 255.0f);
			output[idx + 1] = (unsigned char)(color.y * 255.0f);
			output[idx + 2] = (unsigned char)(color.z * 255.0f);
		}
	}
	std::cout << "Rendering Done!" << std::endl;
}
