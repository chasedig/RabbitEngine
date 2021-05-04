#pragma once
#include "Component.h"
#include <vector>
#include <RBT/graphics/Vertex.h>
#include <RBT/graphics/Mesh.h>
namespace RBT
{
	struct MeshComponent : Component
	{
		MeshComponent(Mesh* mesh)
		{
			this->mesh = mesh;
		}
		Mesh* mesh;
	};
}