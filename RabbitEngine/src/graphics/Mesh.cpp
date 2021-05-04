#include <RBT/graphics/Mesh.h>
#include <glad/glad.h>
#include <iostream>

namespace RBT
{

	Mesh::Mesh()
	{
		this->vertices = {};
		this->modelMatrix = glm::mat4(1.0f);
	}

	Mesh::Mesh(std::vector<Vertex> vertices)
	{
		this->vertices = vertices;
		this->modelMatrix = glm::mat4(1.0f);
	}

	void Mesh::setupMesh()
	{
		// Generate VAO, VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		// Vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position)); // Could just do 0, but offsetof(Vertex, Position) is safer.

		// Vertex normals
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, sizeof(float) * 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		glBindVertexArray(0);
	}

}
