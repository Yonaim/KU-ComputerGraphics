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
