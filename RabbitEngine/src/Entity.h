#pragma once
#include "components/Component.h"
#include <vector>
namespace RBT
{

	class World; // Forward declaration

	class Entity
	{
		public:
			Entity();
			Entity(std::vector<Component*> components);
			~Entity();
			template <class ComponentType>
			ComponentType* GetComponent();
			template <class ComponentType>
			void SetComponent(Component component);
			template<class ComponentType>
			void RemoveComponent();
			World* world;
			std::vector<Component*> components;
	};
}