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
