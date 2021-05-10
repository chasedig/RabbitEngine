#pragma once
#include <RBT/graphics/Color.h>
namespace RBT
{
	struct LightComponent : Component // Light base class
	{
		LightComponent(Color color, float power)
		{
			this->color = color;
			this->power = power;
		}
		Color color;
		float power;
	};
}