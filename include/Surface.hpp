#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "Material.hpp"
#include "Ray.hpp"
#include "hitRecord.h"
#include <glm/glm.hpp>

class Surface
{
  protected:
	glm::vec3 pos;
	Material  material;

  public:
	Surface(/* args */);
	Surface(glm::vec3 pos);
	virtual ~Surface();
	void         setPosition(glm::vec3 pos);
	virtual bool intersect(hitRecord *hit, Ray &ray, float tMin,
						   float tMax) const;
};

#endif
