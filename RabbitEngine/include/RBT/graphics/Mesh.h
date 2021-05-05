#pragma once
#include "Vertex.h"
#include <vector>
namespace RBT
{
	class Mesh
	{
		public:
			unsigned int VAO, VBO, EBO;
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			Mesh();
			Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
			void setupMesh();
	};
}