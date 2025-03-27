#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "Camera.hpp"
#include "Surface.hpp"

class Scene
{
  private:
	std::vector<Surface *> surfaces;
	Camera                 camera;

  public:
	Scene();
	~Scene();

	void                    addSurface(Surface *surface);
	Camera                 &getCamera();
	std::vector<Surface *> &getSurfaces();
	glm::vec3               trace(Ray &ray, float tMin, float tMax) const;
};

#endif
