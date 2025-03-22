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

void Scene::setCameraEye(glm::vec3 eye)
{
}

void Scene::setCameraDirection(glm::vec3 right, glm::vec3 up, glm::vec3 forward)
{
}
