#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <glm/glm.hpp>

class PointLight
{
  private:
	glm::vec3 pos;
	glm::vec3 color;
	float     intensity;
	// no fall off for now

  public:
	PointLight(/* args */);
	~PointLight();
};

PointLight::PointLight(/* args */)
{
}

PointLight::~PointLight()
{
}

#endif
