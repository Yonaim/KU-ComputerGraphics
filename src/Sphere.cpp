#include "Sphere.hpp"

Sphere::Sphere()
{
}

Sphere::Sphere(glm::vec3 pos, float radius) : Surface(pos)
{
	this->radius = radius;
}

Sphere::~Sphere()
{
}

void Sphere::setPosition(glm::vec3 pos)
{
}
