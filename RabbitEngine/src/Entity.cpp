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