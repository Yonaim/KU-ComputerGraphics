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

#include "Scene.hpp"
#include "constant.h"
#include "settings.h"

/*
	1. 레이 생성 (카메라 위치 - 현 픽셀 중심 좌표)
	2. intersection 검사, 가장 가까운 t 찾기
	2. 검사 결과에 따라 흰색 혹은 검은색으로
*/
void render(Scene &scene, Camera &camera)
{
	glm::vec3 color;
	Ray       ray;

	for (int y = 0; y < SCR_HEIGHT; y++)
	{
		for (int x = 0; x < SCR_WIDTH; x++)
		{
			ray   = camera.getRay(x, y);
			color = scene.trace(ray, 0, FLT_INF);
			// TODO: 텍스처에 픽셀 컬러 담기
		}
	}
	// TODO: 스크린 프레임버퍼에 텍스처를 렌더링
}
