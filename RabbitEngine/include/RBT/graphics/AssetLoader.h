#pragma once
#include <string>
#include <RBT/graphics/Mesh.h>
namespace RBT
{
	namespace AssetLoader
	{
		Mesh* LoadMeshFromPath(std::string filepath); // Loads the entire scene as a singular mesh, despite it having possibly multiple components
	}
}