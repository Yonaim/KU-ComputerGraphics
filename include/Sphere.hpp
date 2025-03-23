#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <Surface.hpp>
#include <glm/glm.hpp>

class Sphere : public Surface
{
  private:
	float radius;

  public:
	Sphere();
	Sphere(glm::vec3 pos, float radius);
	~Sphere();
	virtual bool intersectAnalytic(Ray &ray, hitResult *hit, float tMin,
								   float tMax) const;
};

#endif
