#include "PointLight.hpp"

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

PointLight::PointLight(glm::vec3 pos, glm::vec3 color, float intensity)
	: pos(pos), color(color), intensity(intensity)
{
}
