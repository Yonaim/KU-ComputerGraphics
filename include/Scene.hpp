#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "Camera.hpp"
#include "Surface.hpp"
#include "PointLight.hpp"

class Scene
{
  private:
	Camera                    camera;
	std::vector<Surface *>    surfaces;
	std::vector<PointLight *> lights;

  public:
	Scene();
	~Scene();

	void                       addSurface(Surface *surface);
	Camera                    &getCamera();
	std::vector<Surface *>    &getSurfaces();
	std::vector<PointLight *> &getLights();
	glm::vec3                  trace(Ray &ray, float tMin, float tMax);
};

#endif
