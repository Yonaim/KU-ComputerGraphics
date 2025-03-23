#ifndef IMAGEPLANE_HPP
#define IMAGEPLANE_HPP

#include "settings.hpp"
#include <glm/glm.hpp>

class ImagePlane
{
  private:
	float left;
	float right;
	float top;
	float bottom;

  public:
	ImagePlane();
	ImagePlane(float left, float right, float top, float bottom);
	~ImagePlane();
	glm::vec2 pixelToUV(int ix, int iy);
};

#endif
