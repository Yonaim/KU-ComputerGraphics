#include "Plane.hpp"
#include "constant.h"
#include "hitResult.h"
#include <cmath>
#include <glm/glm.hpp>

Plane::Plane()
{
}

Plane::Plane(glm::vec3 pos, glm::vec3 normal) : Surface(pos)
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

// 평면의 식에 ray 대입
// 만약 n * d = 0일시 ray가 평면과 평행 혹은 평면에 포함
bool Plane::intersect(hitResult *hit, Ray &ray, float tMin, float tMax) const
{
	/*
		평면의 방정식: n * (P - P0) = 0
		Ray의 방정식: R(t) = O + t * d

		Ray의 방정식을 평면 방정식에 대입:
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
			// hit->point = ray.pointAt(t);
			return (true);
		}
	}
	return (false);
}
