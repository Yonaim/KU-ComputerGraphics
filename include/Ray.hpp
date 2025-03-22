#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

class Ray
{
  private:
	glm::vec3 origin;
	glm::vec3 dir;

  public:
	Ray(/* args */);
	~Ray();
};

#endif
