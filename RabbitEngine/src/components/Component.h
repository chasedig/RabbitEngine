#pragma once
namespace RBT
{
	class Entity; // Forward declaration

	struct Component
	{
		Entity* entity;
		virtual ~Component() {};
		const char* c = "hi";
	};
}