#ifndef IMAGEPLANE_HPP
#define IMAGEPLANE_HPP

#include "settings.h"
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
	void      setCoordinates(float left, float right, float top, float bottom);
	glm::vec2 pixelToUV(int ix, int iy) const;
};

#endif
