#ifndef HITRECORD_H
#define HITRECORD_H

#include <glm/glm.hpp>
#include "Material.hpp"
#include "Ray.hpp"

class Surface;

typedef struct
{
	Surface  *surface;  // the hit surface
	float     t;        // distance from the ray origin to the hit point
	glm::vec3 normal;   // normal at the hit point
	glm::vec3 point;    // hit point
	Ray       ray;      // the ray that hits the surface
	Material *material; // the material of the surface
} hitRecord;

#endif
