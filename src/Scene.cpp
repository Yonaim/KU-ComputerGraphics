#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
	// free allocated memory for surfaces
	// because the materials are shared pointer, don't need to free them
	std::vector<Surface *>::const_iterator it = this->surfaces.begin();
	while (it < this->surfaces.end())
	{
		delete (*it);
		it++;
	}
	this->surfaces.clear();

	// free allocated memory for lights
	std::vector<PointLight *>::const_iterator it2 = this->lights.begin();
	while (it2 < this->lights.end())
	{
		delete (*it2);
		it2++;
	}
	this->lights.clear();
}

void Scene::setBackgroundColor(glm::vec3 color)
{
	this->background = color;
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
glm::vec3 Scene::trace(Ray &ray, float tMin, float tMax)
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
		return (hit_closest.surface->shade(&hit_closest, this->lights));
	else
		return (glm::vec3(0, 0, 0));
}
