#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "Material.hpp"
#include "Ray.hpp"
#include "hitRecord.h"
#include "PointLight.hpp"
#include <glm/glm.hpp>

class Surface
{
  protected:
	glm::vec3 pos;
	Material *material; // not a pointer now

  public:
	Surface(/* args */);
	Surface(glm::vec3 pos, Material *material);
	virtual ~Surface();

	Material    *getMaterial() const;
	void         setPosition(glm::vec3 pos);
	virtual bool intersect(hitRecord *hit, Ray &ray, float tMin,
						   float tMax) const;
	glm::vec3    shade(hitRecord *hit, std::vector<PointLight *> &lights) const;
};

#endif
