#include "Renderer.hpp"
#include "Scene.hpp"
#include "constant.h"
#include "settings.h"
#include <cstring>
#include "debug.h"

Renderer::Renderer()
{
	this->output.resize(SCR_WIDTH * SCR_HEIGHT * 3);
}

Renderer::~Renderer()
{
}

// Perform gamma correction with γ = 2.2
static void linear_to_gamma(glm::vec3 &color)
{
	color.x = pow(color.x, 1.0f / 2.2f);
	color.y = pow(color.y, 1.0f / 2.2f);
	color.z = pow(color.z, 1.0f / 2.2f);
	color.x = glm::clamp(color.x, 0.0f, 1.0f);
	color.y = glm::clamp(color.y, 0.0f, 1.0f);
	color.z = glm::clamp(color.z, 0.0f, 1.0f);
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
#ifdef PRINT_MSG_PROCESSING_LINE_NUMBER
		std::cout << "Processing line number " << y + 1 << "..." << std::endl;
#endif
		for (int x = 0; x < SCR_WIDTH; x++)
		{
			ray   = camera.getRay(x, y);
			color = scene.trace(ray, 0, FLT_INF);
			linear_to_gamma(color);

			int idx         = (y * SCR_WIDTH + x) * 3;
			output[idx]     = (unsigned char)(color.x * 255.0f);
			output[idx + 1] = (unsigned char)(color.y * 255.0f);
			output[idx + 2] = (unsigned char)(color.z * 255.0f);
		}
	}
	std::cout << "Rendering Done!" << std::endl;
}
