#include "Renderer.hpp"
#include "Scene.hpp"
#include "constant.h"
#include "settings.h"
#include <cstring>

Renderer::Renderer()
{
	memset(output, 0, SCR_WIDTH * SCR_HEIGHT * 3);

	// 텍스처 생성
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// 텍스처 파라미터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// 초기 텍스처 데이터 설정
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, output);
}

Renderer::~Renderer()
{
	glDeleteTextures(1, &textureID);
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

/*
	1. 레이 생성 (카메라 위치 - 현 픽셀 중심 좌표)
	2. intersection 검사, 가장 가까운 t 찾기
	2. 검사 결과에 따라 흰색 혹은 검은색으로
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
