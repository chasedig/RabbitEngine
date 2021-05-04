#include <RBT/graphics/Camera.h>
#include <iostream>
namespace RBT
{
	Camera::Camera(float FOV, float near, float far)
	{
		this->FOV = FOV;
		this->near = near;
		this->far = far;
		this->position = glm::vec3(0.0f, 0.0f, -10);
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
		glm::vec3 Front;
		Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		Front.y = sin(glm::radians(pitch));
		Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(Front);
		// also re-calculate the Right and Up vector
		right = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up = glm::normalize(glm::cross(right, front));
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