#pragma once
#include <RBT/components/LightComponent.h>
namespace RBT
{
	struct PointLightComponent : LightComponent
	{
		PointLightComponent(Color color, float power)
		{
			this->color = color;
			this->power = power;
		}
	};
}