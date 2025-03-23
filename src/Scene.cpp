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
