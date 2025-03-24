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
	Material  material;

  public:
	Surface(/* args */);
	Surface(glm::vec3 pos);
	virtual ~Surface();
	void              setPosition(glm::vec3 pos);
	virtual bool intersect(hitResult *hit, Ray &ray, float tMin, float tMax) const;
};

#endif
