#include "Camera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setEye(glm::vec3 eye)
{
	this->eye = eye;
}

void Camera::setDirection(glm::vec3 right, glm::vec3 up, glm::vec3 forward)
{
	const glm::vec3 crossRightUp      = glm::cross(right, up);
	const glm::vec3 crossRightForward = glm::cross(right, forward);
	const glm::vec3 crossUpForward    = glm::cross(up, forward);

	// check orthogonal
	if (glm::length(crossRightUp) < (1 + EPSILON)
		&& glm::length(crossRightForward) < (1 + EPSILON)
		&& glm::length(crossUpForward) < (1 + EPSILON))
	{
		this->right   = right;
		this->up      = up;
		this->forward = forward;
	}
	else
		std::cerr << "The camera direction vectors are not orgthogonal"
				  << std::endl;
}

void Camera::setDistance(float distance)
{
	this->distance = distance;
}

void Camera::setImagePlane(float left, float right, float top, float bottom)
{
	this->imgPlane.setCoordinates(left, right, top, bottom);
}

// camera space to world space
glm::vec3 Camera::uvToWorld(glm::vec2 uv) const
{
	const glm::vec3 img_plane_center = eye - (forward * distance);
	return (img_plane_center + (uv.x * right) + (uv.y * up));
}

/*
	Generating eye rays—perspective
	- direction: s - eye
	- s: screen point
	- In camera spcae, s = (u, v, –d)
	- In world space, s = (image_plane_center + (u * right) + (v * up)
*/
Ray Camera::getRay(int ix, int iy) const
{
	const glm::vec2 uv  = this->imgPlane.pixelToUV(ix, iy);
	const glm::vec3 s   = uvToWorld(uv);
	const Ray       ray = Ray(this->eye, glm::vec3(s - this->eye));

	return (ray);
}
