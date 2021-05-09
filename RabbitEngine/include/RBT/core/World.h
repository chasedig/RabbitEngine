#pragma once
#include "Entity.h"
namespace RBT
{
	class World
	{
		public:
			World();
			std::vector<Entity*> entities;
			std::map<Entity*, std::map<std::type_index, Component*>> components;
			template<typename ComponentType>
			std::vector<ComponentType*> GetComponentsOfType()
			{
				return NULL;
			}
	};
}