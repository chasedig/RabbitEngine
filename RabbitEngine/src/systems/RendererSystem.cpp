#include "RendererSystem.h"
#include "glad/glad.h"
#include "graphics/Window.h"
#include "components/MeshComponent.h"
#include "components/Renderer.h"
#include "components/Transform.h"
namespace RBT
{

	RendererSystem::RendererSystem(Window* window, Camera* camera)
	{
		this->window = window;
		this->camera = camera;
		this->shader = new Shader("vertex.glsl", "fragment.glsl");
	}

	void RendererSystem::Update(World* world)
	{
		//glCullFace(GL_BACK);
		//glEnable(GL_CULL_FACE);

		shader->bind();

		glm::mat4 projectionMatrix = glm::perspective(camera->FOV, window->getAspectRatio(), camera->near, camera->far);
		this->shader->setMat4Uniform("projection", projectionMatrix);

		glm::mat4 viewMatrix = camera->getViewMatrix();
		this->shader->setMat4Uniform("view", viewMatrix);



		for (int e = 0; e < world->entities.size(); e++)
		{
			Entity entity = *world->entities[e];
			Renderer* renderer = entity.GetComponent<Renderer>();
			MeshComponent* meshComponent = entity.GetComponent<MeshComponent>();
			Transform* transform = entity.GetComponent<Transform>();
			if (renderer && meshComponent && transform)
			{
				Mesh* mesh = meshComponent->mesh;
				glm::mat4 modelMatrix = mesh->modelMatrix;
				this->shader->setMat4Uniform("model", modelMatrix);
				glBindVertexArray(mesh->VAO);
				glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh->vertices.size());
				glBindVertexArray(0);
			}
		}
		shader->unbind();
	}
}
