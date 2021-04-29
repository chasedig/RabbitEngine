#pragma once
#include "Component.h"
#include <vector>
#include <graphics/Vertex.h>
#include <graphics/Mesh.h>
namespace RBT
{
	struct MeshComponent : Component
	{
		Mesh* mesh;
	};
}