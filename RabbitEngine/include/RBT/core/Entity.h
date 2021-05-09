#pragma once
#include "RBT/components/Component.h"
#include <iostream>
#include <RBT/core/World.h>
namespace RBT
{

	class World;

	class Entity
	{
	public:
		World* world;

		template<typename ComponentType> ComponentType* GetComponent()
		{
			return this->world->GetComponent<ComponentType>(this);
		}

		template<typename ComponentType>
		void SetComponent(ComponentType component)
		{
			this->world->SetComponent(this, component);
		}

		template<typename ComponentType>
		void RemoveComponent()
		{
			this->world->RemoveComponent<ComponentType>(this);
		}
	};
};