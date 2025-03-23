#ifndef HITRESULT_HPP
#define HITRESULT_HPP

#include <glm/glm.hpp>
class Surface;

typedef struct
{
	Surface  *surface;
	float     t;
	glm::vec3 normal;
	glm::vec3 point;
} hitResult;

#endif
