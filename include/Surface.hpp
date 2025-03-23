#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "Material.hpp"
#include "Ray.hpp"
#include "hitResult.h"
#include <glm/glm.hpp>

class Surface
{
  protected:
	glm::vec3 pos;
	Material  material; // 추후 사용

	virtual bool intersectAnalytic(Ray &ray, hitResult *hit, float tMin,
								   float tMax) const;

  public:
	Surface(/* args */);
	Surface(glm::vec3 pos);
	~Surface();
	void              setPosition(glm::vec3 pos);
	virtual hitResult intersect(Ray &ray, float tMin, float tMax) const;
};

#endif
