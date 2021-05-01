#include "Entity.h"
#include "components/Component.h"
#include "World.h"

RBT::Entity::Entity()
{
	this->components = {};
}