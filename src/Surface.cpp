#include "Surface.hpp"

Surface::Surface(/* args */)
{
}

Surface::Surface(glm::vec3 pos) : pos(pos)
{
}

Surface::~Surface()
{
}

hitResult Surface::intersect(Ray &ray, float tMin, float tMax) const
{
	float    t = std::numeric_limits<float>::infinity();
	Surface *surface = NULL;

	// todo: this와 ray의 교차 검사 수행
	
	return ((hitResult){surface, t});
}
