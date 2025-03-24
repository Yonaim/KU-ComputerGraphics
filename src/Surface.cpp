#include "Surface.hpp"

Surface::Surface(/* args */)
{
}

Surface::Surface(glm::vec3 pos) : pos(pos)
{
}

Surface::~Surface()
{
}

void Surface::setPosition(glm::vec3 pos)
{
	this->pos = pos;
}


bool	Surface::intersect(hitResult *hit, Ray &ray, float tMin, float tMax) const
{
	// virtual function
	// each surface has a different equation
	return (false);
}
