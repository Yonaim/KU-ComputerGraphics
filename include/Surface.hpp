#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "Material.hpp"
#include "Ray.hpp"
#include "hitResult.hpp"
#include <glm/glm.hpp>

class Surface
{
  private:
	glm::vec3 pos;
	Material  material; // 추후 사용

  public:
	Surface(/* args */);
	Surface(glm::vec3 pos);
	~Surface();
	hitResult intersect(Ray &ray, float tMin, float tMax) const;
};

#endif
