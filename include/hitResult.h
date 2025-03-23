#ifndef HITRESULT_H
#define HITRESULT_H

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
