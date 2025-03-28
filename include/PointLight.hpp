#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <glm/glm.hpp>

class PointLight
{
  private:
  public:
	glm::vec3 pos;
	glm::vec3 color;
	float     intensity;
	// no fall off for now

	PointLight(/* args */);
	~PointLight();
	PointLight(glm::vec3 pos, glm::vec3 color, float intensity);
};

#endif
