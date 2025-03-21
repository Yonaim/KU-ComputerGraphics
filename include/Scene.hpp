#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "Camera.hpp"
#include "Surface.hpp"

class Scene
{
  private:
	std::vector<Surface> surfaces;
	Camera camera;

  public:
	Scene(/* args */);
	~Scene();
};

Scene::Scene(/* args */)
{
}

Scene::~Scene()
{
}

#endif
