#include "Ray.hpp"

Ray::Ray()
{
}

Ray::Ray(glm::vec3 origin, glm::vec3 dir) : origin(origin), dir(dir)
{
}

Ray::~Ray()
{
}

glm::vec3 Ray::getDirection() const
{
	return (this->dir);
}

glm::vec3 Ray::getOrigin() const
{
	return (this->origin);
}

glm::vec3 Ray::pointAt(float t) const
{
	return (this->origin + (t * this->dir));
}
