#pragma once
#include "glm/ext.hpp"
namespace RBT
{
	class Camera
	{
		public:
			Camera(float FOV, float near, float far);
			glm::mat4 getViewMatrix();
			void updateCameraVectors();
			void ProcessMouseMovement(double xoffset, double yoffset, bool constrainPitch);
			float FOV;
			float near;
			float far;

			float Sensitivity = 0.1f;
			float Speed = 50;

			glm::vec3 position;

			glm::vec3 front;
			glm::vec3 right;
			glm::vec3 up;

			float yaw = 360;
			float pitch = -90.0f;
	};
}