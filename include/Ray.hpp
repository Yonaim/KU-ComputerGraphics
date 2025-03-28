#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

class Ray
{
  private:
  public:
	glm::vec3 origin;    // origin
	glm::vec3 direction; // direction

	Ray();
	Ray(glm::vec3 origin, glm::vec3 direction);
	~Ray();
	glm::vec3 getDirection() const;
	glm::vec3 getOrigin() const;
	glm::vec3 pointAt(float t) const;
};

#endif
