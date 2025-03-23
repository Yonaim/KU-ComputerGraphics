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

void ImagePlane::setCoordinates(float left, float right, float top,
								float bottom)
{
	this->left   = left;
	this->right  = right;
	this->top    = top;
	this->bottom = bottom;
}

// screen space to camera space
glm::vec2 ImagePlane::pixelToUV(int ix, int iy) const
{
	/*
		U: horizontal
		V: vertical
		SCR_WIDTH: count of horizontal pixels
		SCR_HEIGHT: count of vertical pixels
	*/
	const float image_plane_width  = right - left;
	const float image_plane_height = top - bottom;
	const float u = left + (image_plane_width) * ((ix + 0.5) / SCR_WIDTH);
	const float v = right + (image_plane_height) * ((iy + 0.5) / SCR_HEIGHT);

	return (glm::vec2(u, v));
}
