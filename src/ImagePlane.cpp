#include "ImagePlane.hpp"

ImagePlane::ImagePlane()
{
}

ImagePlane::ImagePlane(float left, float right, float top, float bottom)
	: left(left), right(right), top(top), bottom(bottom)
{
}

ImagePlane::~ImagePlane()
{
}

/*
U: horizontal, V: vertical
*/
glm::vec2 ImagePlane::pixelToUV(int ix, int iy)
{
	// SCR_WIDTH = horizontal pixel count
	// SCR_HEIGHT = vertical pixel count
	const float image_plane_width  = right - left;
	const float image_plane_height = top - bottom;
	const float u = left + (image_plane_width) * ((ix + 0.5) / SCR_WIDTH);
	const float v = right + (image_plane_height) * ((iy + 0.5) / SCR_HEIGHT);

	return (glm::vec2(u, v));
}
