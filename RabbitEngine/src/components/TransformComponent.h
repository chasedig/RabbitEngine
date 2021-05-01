#pragma once
#include "Component.h"
#include <glm/ext/matrix_float4x4.hpp>
namespace RBT
{
	struct TransformComponent : Component
	{
		TransformComponent(glm::mat4 transform)
		{
			this->transform = transform;
		}
		glm::mat4 transform = glm::mat4(1.0f);
	};
}