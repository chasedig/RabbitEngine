#pragma once
#include <map>
#include <typeindex>
#include <RBT/components/Component.h>
#include <vector>
namespace RBT
{
	class Entity;

	class World
	{
		public:
			World();
			std::vector<Entity*> entities;
			std::map<Entity*, std::map<std::type_index, Component*>> components;
			
			int AddEntity(Entity* entity);
			template<typename ComponentType> ComponentType* GetComponent(Entity* entity)
			{
				Component* component = components[entity][typeid(ComponentType)];
				if (component)
				{
					return static_cast<ComponentType*>(component);
				}
				return NULL;
			}
			template<typename ComponentType> std::vector<ComponentType*> GetComponentsOfType()
			{
				std::vector<ComponentType*> components;
				for (Entity* entity : entities)
				{
					ComponentType* component = this->GetComponent(entity);
					if (component)
					{
						components.push_back(component);
					}
				}
			}
			template<typename ComponentType> ComponentType* SetComponent(Entity* entity, ComponentType* component)
			{
				component->entity = entity;
				this->components[entity][typeid(ComponentType)] = component;
				return this->GetComponent<ComponentType>(entity);
			}

			template<typename ComponentType>
			void RemoveComponent(Entity* entity)
			{
				ComponentType* existingComponent = this->GetComponent<ComponentType>(entity);
				if (existingComponent)
				{
					delete existingComponent;
					components[entity].erase(typeid(ComponentType));
				}
			}
		private:
			unsigned int lastEntityID = 0;
	};
}