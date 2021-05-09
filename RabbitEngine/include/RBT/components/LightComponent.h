#pragma once
#include <RBT/graphics/Color.h>
namespace RBT
{
	struct LightComponent // Light base class
	{
		Color color;
		float power;
	};
}