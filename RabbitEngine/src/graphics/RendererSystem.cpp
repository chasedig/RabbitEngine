#include "RendererSystem.h"
#include "glad/glad.h"
#include "core/Window.h"
#include "components/MeshComponent.h"
#include "components/RendererComponent.h"
#include "components/TransformComponent.h"
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
			Entity* entity = world->entities[e];
			RendererComponent* renderer = entity->GetComponent<RendererComponent>();
			MeshComponent* meshComponent = entity->GetComponent<MeshComponent>();
			TransformComponent* transform = entity->GetComponent<TransformComponent>();

			if (renderer && meshComponent && transform)
			{
				if (renderer->enabled == true)
				{
					Mesh mesh = *meshComponent->mesh;
					glm::mat4 modelMatrix = transform->transform;
					this->shader->setMat4Uniform("model", modelMatrix);
					glBindVertexArray(mesh.VAO);
					glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.vertices.size());
					glBindVertexArray(0);
				}
			}
		}
		shader->unbind();
	}
}
