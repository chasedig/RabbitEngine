#include "Entity.h"
#include "components/Component.h"
#include "World.h"

RBT::Entity::Entity()
{
	this->components = {};
}

RBT::Entity::Entity(std::vector<Component*> components)
{
	this->components = components;
}

RBT::Entity::~Entity()
{
	for (int c = 0; c < this->components.size(); c++)
	{
		delete this->components[c];
	}
}

template<typename ComponentType>
ComponentType* RBT::Entity::GetComponent()
{
	for (int c = 0; c < this->components.size(); c++)
	{
		auto* derived = dynamic_cast<ComponentType*>(this->components[c]);
		if (derived)
		{
			return derived;
		}
	}
	return NULL;
}

template<typename ComponentType>
void RBT::Entity::SetComponent(Component component)
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
void RBT::Entity::RemoveComponent()
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