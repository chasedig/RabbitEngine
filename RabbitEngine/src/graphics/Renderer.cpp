#include "Renderer.h"
#include "glad/glad.h"
#include "Window.h"
namespace RBT
{

	Renderer::Renderer(Window* window, Camera* camera)
	{
		this->window = window;
		this->camera = camera;
		this->shader = new Shader("vertex.glsl", "fragment.glsl");
		Mesh* mesh = new Mesh();
		mesh->vertices = {Vertex(glm::vec3(0,0,0), glm::vec3(0,0,1), glm::vec2(0,0)), Vertex(glm::vec3(1,0,0), glm::vec3(0,0,1), glm::vec2(0,0)), Vertex(glm::vec3(1,1,0), glm::vec3(0,0,1), glm::vec2(0,0)) };
		mesh->modelMatrix = glm::translate(mesh->modelMatrix, glm::vec3(0, 0, -5));
		mesh->setupMesh();
		meshes.push_back(mesh);
	}

	void Renderer::Render()
	{
		//glCullFace(GL_BACK);
		//glEnable(GL_CULL_FACE);

		shader->bind();

		glm::mat4 projectionMatrix = glm::perspective(camera->FOV, window->getAspectRatio(), camera->near, camera->far);
		this->shader->setMat4Uniform("projection", projectionMatrix);

		glm::mat4 viewMatrix = camera->getViewMatrix();
		this->shader->setMat4Uniform("view", viewMatrix);

		for (int m = 0; m < meshes.size(); m++)
		{
			Mesh mesh = *meshes[m];
			glm::mat4 modelMatrix = mesh.modelMatrix;
			this->shader->setMat4Uniform("model", modelMatrix);
			glBindVertexArray(mesh.VAO);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.vertices.size());
			glBindVertexArray(0);
		}
		shader->unbind();
	}
}
