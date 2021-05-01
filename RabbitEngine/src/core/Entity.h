#pragma once
#include "components/Component.h"
#include <vector>
#include <iostream>
#include <map>
#include <typeindex>
#include <unordered_map>
namespace RBT
{

	class World; // Forward declaration

	class Entity
	{
	public:
		Entity();
		template<typename ComponentType>
		ComponentType* GetComponent()
		{
			ComponentType* derived = dynamic_cast<ComponentType*>(components[typeid(ComponentType)]);
			if (derived)
			{
				return derived;
			}
			return NULL;
		}

		template<typename ComponentType>
		void SetComponent(ComponentType* component)
		{
			auto* existingComponent = this->GetComponent<ComponentType>();
			if (existingComponent)
			{
				this->RemoveComponent<ComponentType>();
			}
			component->entity = this;
			components[typeid(ComponentType)] = component;
		}

		template<typename ComponentType>
		void RemoveComponent()
		{
			ComponentType* existingComponent = this->GetComponent<ComponentType>();
			if (existingComponent)
			{
				//this->components:erase(typeid(ComponentType));
			}
		}

		World* world;
		std::map<std::type_index, Component*> components;
	};
};