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
