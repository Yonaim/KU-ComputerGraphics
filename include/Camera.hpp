#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ImagePlane.hpp"
#include "Ray.hpp"
#include "constant.h"
#include "settings.h"
#include <glm/glm.hpp>
#include <iostream>

class Camera
{
  private:
	glm::vec3  eye;      // position of camera
	glm::vec3  right;    // u
	glm::vec3  up;       // v
	glm::vec3  forward;  // w
	float      distance; // distance from image plane (aka. focal length)
	ImagePlane imgPlane; // image plane

	glm::vec3 uvToWorld(glm::vec2 uv) const;

  public:
	Camera();
	~Camera();
	void setEye(glm::vec3 eye);
	void setDirection(glm::vec3 right, glm::vec3 up, glm::vec3 forward);
	void setDistance(float distance);
	void setImagePlane(float left, float right, float top, float bottom);
	Ray  getRay(int ix, int iy) const;
};

#endif
