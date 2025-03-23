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

hitResult Surface::intersect(Ray &ray, float tMin, float tMax) const
{
	hitResult hit;

	hit.t       = tMax;
	hit.surface = NULL;

	if (intersectAnalytic(ray, &hit, tMin, tMax))
	{
		hit.surface = (Surface *)this;
		hit.point = ray.pointAt(hit.t); // 추후 사용
	}

	return (hit);
}

bool Surface::intersectAnalytic(Ray &ray, hitResult *hit, float tMin,
								float tMax) const
{
	// virtual function
	// each surface has a different equation
	return (false);
}
