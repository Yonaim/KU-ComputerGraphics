#include "Sphere.hpp"

Sphere::Sphere()
{
}

Sphere::Sphere(glm::vec3 pos, Material *material, float radius)
	: Surface(pos, material)
{
	this->radius = radius;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(hitRecord *hit, Ray &ray, float tMin, float tMax) const
{
	/*
		구의 방정식: (P - C) * (P - C) = r^2
		Ray의 방정식: R(t) = O + t * d

		((O + t * d) - C) · ((O + t * d) - C) = r^2
		-> t^2 * (d · d) + 2 * t * (d · (O - C)) + ((O - C) · (O - C) - r^2)
		= 0
		-> t = [-(p·d) ± √((p·d)^2 - (d·d)(p·p - r^2))] / (d·d)
			(p = O - C)
	*/
	const glm::vec3 p = ray.getOrigin() - pos;
	const glm::vec3 d = ray.getDirection();

	const float d_dot_p = glm::dot(d, p);
	const float d_dot_d = glm::dot(d, d);
	const float p_dot_p = glm::dot(p, p);

	// discriminant
	const float disc
		= d_dot_p * d_dot_p - d_dot_d * (p_dot_p - radius * radius);

	if (disc < 0)
		return (false);

	const float sqrtDisc = sqrt(disc);

	// solution
	const float t1 = (-d_dot_p - sqrtDisc) / d_dot_d;
	const float t2 = (-d_dot_p + sqrtDisc) / d_dot_d;

	if (t1 >= tMin && t1 <= tMax)
	{
		hit->t = t1;
		hit->point = ray.pointAt(t1);
	}
	else if (t2 >= tMin && t2 <= tMax)
	{
		hit->t     = t2;
		hit->point = ray.pointAt(t2);
	}
	else
		return (false);
	hit->surface  = (Surface *)this;
	hit->normal   = glm::normalize(hit->point - pos);
	hit->ray      = ray;
	hit->material = this->material;
	return (true);
}
