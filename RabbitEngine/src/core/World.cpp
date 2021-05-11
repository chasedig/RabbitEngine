#include <RBT/core/World.h>
#include <RBT/core/Entity.h>

RBT::World::World()
{
	this->entities = {};
}

int RBT::World::AddEntity(Entity* entity)
{
	entity->world = this;
	this->entities.push_back(entity);
	return this->entities.size() - 1;
}

void RBT::World::RemoveEntity(int id)
{
	Entity* entity = this->entities[id];
	if (entity)
	{
		this->entities.erase(this->entities.begin() + id);
		this->components.erase(entity);
		delete entity;
	}
}