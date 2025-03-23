#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "Camera.hpp"
#include "Surface.hpp"

class Scene
{
  private:
	std::vector<Surface> surfaces;
	Camera               camera;

  public:
	Scene();
	~Scene();

	void addSurface(const Surface &surface);
	void setCameraImagePlane(float left, float right, float top, float bottom);
	void setCameraEye(glm::vec3 eye);
	void setCameraDistance(float distance);
	void setCameraDirection(glm::vec3 right, glm::vec3 up, glm::vec3 forward);
};

#endif
