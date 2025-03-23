#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::addSurface(const Surface &surface)
{
	this->surfaces.push_back(surface);
}

void Scene::setCameraImagePlane(float left, float right, float top,
								float bottom)
{
	this->camera.setImagePlane(left, right, top, bottom);
}

void Scene::setCameraEye(glm::vec3 eye)
{
	this->camera.setEye(eye);
}

void Scene::setCameraDistance(float distance)
{
	this->camera.setDistance(distance);
}

void Scene::setCameraDirection(glm::vec3 right, glm::vec3 up, glm::vec3 forward)
{
	this->camera.setDirection(right, up, forward);
}

// find the hitted surface with smallest t
glm::vec3 Scene::trace(Ray &ray, float tMin, float tMax) const
{
	std::vector<Surface>::const_iterator it = this->surfaces.begin();
	hitResult                            nearest_hit;

	nearest_hit.surface = NULL;
	nearest_hit.t       = tMax;
	while (it < this->surfaces.end())
	{
		it->intersect(ray, tMin, nearest_hit.t);
		it++;
	}

	if (nearest_hit.surface != NULL)
		return (glm::vec3(255, 255, 255));
	else
		return (glm::vec3(0, 0, 0));
}
