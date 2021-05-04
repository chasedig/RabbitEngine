#pragma once
#include "Component.h"
#include <RBT/graphics/Color.h>
namespace RBT
{
	struct ColorMaterialComponent : Component
	{
		ColorMaterialComponent(Color color)
		{
			this->color = color;
		}
		Color color;
	};
}