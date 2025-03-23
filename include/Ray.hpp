#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

class Ray
{
  private:
	glm::vec3 origin;
	glm::vec3 dir;

  public:
	Ray();
	Ray(glm::vec3 origin, glm::vec3 dir);
	~Ray();
	glm::vec3 getDirection() const;
	glm::vec3 getOrigin() const;
	glm::vec3 pointAt(float t) const;
};

#endif
