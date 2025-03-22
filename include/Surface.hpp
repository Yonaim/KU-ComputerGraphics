#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "Material.hpp"
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
};

#endif
