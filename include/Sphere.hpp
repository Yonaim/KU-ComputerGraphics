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
	void setPosition(glm::vec3 pos);
};

#endif
