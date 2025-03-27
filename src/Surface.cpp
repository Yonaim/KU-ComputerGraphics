#include "Surface.hpp"

Surface::Surface(/* args */)
{
}

Surface::Surface(glm::vec3 pos, Material *material)
	: pos(pos), material(material)
{
}

Surface::~Surface()
{
}

void Surface::setPosition(glm::vec3 pos)
{
	this->pos = pos;
}

bool Surface::intersect(hitRecord *hit, Ray &ray, float tMin, float tMax) const
{
	// virtual function
	// each surface has a different equation
	return (false);
}
