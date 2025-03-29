#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Surface.hpp"
#include <glm/glm.hpp>
#include "Material.hpp"

class Sphere : public Surface
{
  private:
	float radius;

  public:
	Sphere();
	Sphere(glm::vec3 pos, Material *material, float radius);
	virtual ~Sphere();
	virtual bool intersect(hitRecord *hit, Ray &ray, float tMin,
						   float tMax) const override;
};

#endif
