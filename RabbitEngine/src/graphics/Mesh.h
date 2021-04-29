#pragma once
#include "Vertex.h"
#include <vector>
namespace RBT
{
	class Mesh
	{
		public:
			unsigned int VAO, VBO;
			glm::mat4 modelMatrix;
			std::vector<Vertex> vertices;
			Mesh();
			Mesh(std::vector<Vertex> vertices);
			void setupMesh();
	};
}