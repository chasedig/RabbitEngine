#include "Camera.h"
namespace RBT
{
	Camera::Camera(float FOV, float near, float far)
	{
		this->FOV = FOV;
		this->near = near;
		this->far = far;
		this->position = glm::vec3(0.0f, 0.0f, -10.0f);
		this->front = glm::vec3();
		this->right = glm::vec3();
		this->up = glm::vec3();
		updateCameraVectors();
	}

	glm::mat4 Camera::getViewMatrix()
	{
		return glm::lookAt(this->position, this->position - this->front, glm::vec3(0,1,0));
	}

	void Camera::updateCameraVectors()
	{
		glm::vec3 Front = glm::vec3();
		Front.x = (cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
		Front.y = sin(glm::radians(pitch));
		Front.z = (sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
		Front = glm::normalize(Front);
		this->front = Front;
		this->right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), front));
		this->up = glm::normalize(glm::cross(right, front));
	}

	void Camera::ProcessMouseMovement(double xoffset, double yoffset, bool constrainPitch)
	{
		xoffset *= Sensitivity;
		yoffset *= Sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (constrainPitch)
		{
			if (pitch > 89.9f)
			{
				pitch = 89.9f;
			}
			if (pitch < -89.9f)
			{
				pitch = -89.9f;
			}
		}

		this->updateCameraVectors();
	}
}