#include "Plane.hpp"

Plane::Plane()
{
}

Plane::Plane(glm::vec3 pos, glm::vec3 normal) : Surface(pos)
{
	// this->normal = glm::normalize(normal);
}

Plane::~Plane()
{
}

void Plane::setNormal(glm::vec3 normal)
{
}
