#pragma once
#include "Component.h"
namespace RBT
{
	struct RendererComponent : Component
	{
		RendererComponent()
		{
			this->enabled = true;
		}
		bool enabled;
	};
}