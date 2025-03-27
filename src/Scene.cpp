#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::addSurface(Surface *surface)
{
	this->surfaces.push_back(surface);
}

Camera &Scene::getCamera()
{
	return (this->camera);
}

std::vector<Surface *> &Scene::getSurfaces()
{
	return (this->surfaces);
}

std::vector<PointLight *> &Scene::getLights()
{
	return (this->lights);
}

// find the hitted surface with smallest t
glm::vec3 Scene::trace(Ray &ray, float tMin, float tMax) const
{
	std::vector<Surface *>::const_iterator it = this->surfaces.begin();
	hitRecord                              hit_closest;

	hit_closest.surface = NULL;
	hit_closest.t       = tMax;
	while (it < this->surfaces.end())
	{
		hitRecord hit_curr;
		bool      is_hit;

		hit_curr.surface = NULL;
		hit_curr.t       = tMax;
		is_hit = (*it)->intersect(&hit_curr, ray, tMin, hit_closest.t);
		if (is_hit && hit_curr.t < hit_closest.t)
			hit_closest = hit_curr;
		it++;
	}

	if (hit_closest.surface != NULL)
		return (glm::vec3(1.0f, 1.0f, 1.0f));
	else
		return (glm::vec3(0, 0, 0));
}
