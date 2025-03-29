#include "Plane.hpp"
#include "constant.h"
#include "hitRecord.h"
#include <cmath>
#include <glm/glm.hpp>

Plane::Plane()
{
}

Plane::Plane(glm::vec3 pos, Material *material, glm::vec3 normal)
	: Surface(pos, material)
{
	this->normal = glm::normalize(normal);
}

Plane::~Plane()
{
}

void Plane::setNormal(glm::vec3 normal)
{
	this->normal = glm::normalize(normal);
}

// Substitute ray in the expression of the plane
// If n * d = 0, ray is parallel to or contained in the plane
bool Plane::intersect(hitRecord *hit, Ray &ray, float tMin, float tMax) const
{
	/*
		Equation in the plane: n * (P - P0) = 0
		Ray's equation: R(t) = O + t * d

		Substituting Ray's equation into the plane equation:
		n * (O + t * d - P0) = 0
		-> n * (O - P0) + t * (n * d) = 0
		-> t = - (n * (O - P0)) / (n * d)

		numerator = n * (O - P0)
		denominator = n * d
	*/
	const float denom = glm::dot(normal, ray.getDirection());
	float       numer;
	float       t;

	if (fabs(denom) > EPSILON)
	{
		numer = -glm::dot(normal, ray.getOrigin() - pos);
		t     = numer / denom;
		if (tMin < t && t < tMax)
		{
			hit->t       = t;
			hit->surface = (Surface *)this;
			hit->point   = ray.pointAt(t);
			hit->normal  = this->normal;
			hit->ray     = ray;
			hit->material = this->material;
			return (true);
		}
	}
	return (false);
}
