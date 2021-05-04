#pragma once
#include "World.h"
namespace RBT
{
	class System
	{
		public:
			virtual void Update(World* world) = 0;
	};
}