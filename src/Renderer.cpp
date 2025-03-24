#include "Renderer.hpp"
#include "Scene.hpp"
#include "constant.h"
#include "settings.h"
#include <cstring>

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

	// Create checkerboard pattern
	for (int y = 0; y < SCR_HEIGHT; y++)
	{
		for (int x = 0; x < SCR_WIDTH; x++)
		{
			int idx = (y * SCR_WIDTH + x) * 3;
			if ((x / 32 + y / 32) % 2)
			{
				output[idx]     = 255; // Red
				output[idx + 1] = 0;
				output[idx + 2] = 0;
			}
			else
			{
				output[idx]     = 0; // Cyan
				output[idx + 1] = 255;
				output[idx + 2] = 255;
			}
		}
	}

	// Delete previous texture if it exists
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
	}

	// Generate new texture
	glGenTextures(1, &textureID);
	std::cout << "Generated texture ID: " << textureID << std::endl;

	// Check error after generation
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after texture generation: " << error
				  << std::endl;
	}

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after binding texture: " << error
				  << std::endl;
	}

	// Set texture parameters one by one to find the issue
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after WRAP_S: " << error << std::endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after WRAP_T: " << error << std::endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after MIN_FILTER: " << error << std::endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after MAG_FILTER: " << error << std::endl;
	}

	// Initialize with data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, output);

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after texImage2D: " << error << std::endl;
	}
	else
	{
		std::cout << "Texture setup successful" << std::endl;
	}
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
		std::cout << "Processing line number " << y + 1 << "..." << std::endl;
		for (int x = 0; x < SCR_WIDTH; x++)
		{
			ray   = camera.getRay(x, y);
			color = scene.trace(ray, 0, FLT_INF);

			int idx         = (y * SCR_WIDTH + x) * 3;
			output[idx]     = (unsigned char)color.x;
			output[idx + 1] = (unsigned char)color.y;
			output[idx + 2] = (unsigned char)color.z;
		}
	}
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RGB,
					GL_UNSIGNED_BYTE, output);
	std::cout << "Rendering Done!" << std::endl;
}
