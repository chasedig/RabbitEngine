#pragma once
#include "Entity.h"
namespace RBT
{
	class World
	{
		public:
			World();
			std::vector<Entity*> entities;
	};
}