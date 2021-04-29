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
			template<typename ComponentType>
			ComponentType* GetComponent()
			{
				for (int c = 0; c < this->components.size(); c++)
				{
					ComponentType* derived = dynamic_cast<ComponentType*>(this->components[c]);
					if (derived)
					{
						return derived;
					}
				}
				return NULL;
			}

			template<typename ComponentType>
			void SetComponent(Component component)
			{
				Component existingComponent = this->GetComponent<ComponentType>();
				if (existingComponent)
				{
					this->RemoveComponent<ComponentType>();
				}
				component.entity = this;
				this->components.push_back(&component);
			}

			template<typename ComponentType>
			void RemoveComponent()
			{
				Component existingComponent = this->GetComponent<ComponentType>();
				if (existingComponent)
				{
					for (int c = 0; c < this->components.size(); c++)
					{
						if (this->components[c] == existingComponent)
						{
							delete this->components[c];
							this->components.erase(c);
							break;
						}
					}
				}
			}

			World* world;
			std::vector<Component*> components;
	};
}