#ifndef HITRECORD_H
#define HITRECORD_H

#include <glm/glm.hpp>
class Surface;

typedef struct
{
	Surface  *surface;
	float     t;
	glm::vec3 normal;
	glm::vec3 point;
} hitRecord;

#endif
