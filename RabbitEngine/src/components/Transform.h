#pragma once
#include "Component.h"
#include <glm/ext/matrix_float4x4.hpp>
namespace RBT
{
	struct Transform : Component
	{
		glm::mat4 transform;
	};
}