#include <RBT/core/World.h>
#include <RBT/core/Entity.h>

RBT::World::World()
{
	this->entities = {};
}

int RBT::World::AddEntity(Entity* entity)
{
	lastEntityID++;
	entity->world = this;
	this->entities.push_back(entity);
	return this->entities.size() - 1;
}