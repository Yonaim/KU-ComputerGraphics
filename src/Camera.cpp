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
	if (glm::length(crossRightUp) < EPSILON
		&& glm::length(crossRightForward) < EPSILON
		&& glm::length(crossUpForward) < EPSILON)
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
	const glm::vec3 img_plane_center = eye - (forward * forward);

	return (img_plane_center + (uv.x * right) + (uv.y * up));
}

