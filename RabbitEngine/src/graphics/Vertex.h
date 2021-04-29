#pragma once
#include "glm/glm.hpp"
namespace RBT
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TextureCoordinates;
		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord)
		{
			this->Position = position;
			this->Normal = normal;
			this->TextureCoordinates = texCoord;
		}
	};
}