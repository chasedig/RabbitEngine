#include "RendererSystem.h"
#include "glad/glad.h"
#include "core/Window.h"
#include "components/MeshComponent.h"
#include "components/RendererComponent.h"
#include "components/TransformComponent.h"
#include <components/ColorMaterialComponent.h>
namespace RBT
{

	RendererSystem::RendererSystem(Window* window, Camera* camera)
	{
		this->window = window;
		this->camera = camera;
		this->colorShader = new Shader("vertex.glsl", "colorMaterial_frag.glsl");
	}

	void RendererSystem::Update(World* world)
	{
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, window->getWidth(), window->getHeight());
		//glCullFace(GL_BACK);
		//glEnable(GL_CULL_FACE);

		Shader* shader = NULL;


		glm::mat4 projectionMatrix = glm::perspective(camera->FOV, window->getAspectRatio(), camera->near, camera->far);

		glm::mat4 viewMatrix = camera->getViewMatrix();


		for (int e = 0; e < world->entities.size(); e++)
		{
			Entity* entity = world->entities[e];
			RendererComponent* renderer = entity->GetComponent<RendererComponent>();
			MeshComponent* meshComponent = entity->GetComponent<MeshComponent>();
			TransformComponent* transform = entity->GetComponent<TransformComponent>();
			ColorMaterialComponent* colorMaterial = entity->GetComponent<ColorMaterialComponent>();

			if (renderer && meshComponent && transform)
			{
				if (renderer->enabled == true)
				{
					if (colorMaterial)
					{
						shader = colorShader;
						shader->bind();
						shader->setVec3Uniform("color", glm::vec3(colorMaterial->color.R, colorMaterial->color.G, colorMaterial->color.B));
					}

					if (shader)
					{
						shader->setMat4Uniform("projection", projectionMatrix);
						shader->setMat4Uniform("view", viewMatrix);

						Mesh mesh = *meshComponent->mesh;
						glm::mat4 modelMatrix = transform->transform;
						shader->setMat4Uniform("model", modelMatrix);
						glBindVertexArray(mesh.VAO);
						glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.vertices.size());
						glBindVertexArray(0);

						shader->unbind();
					}
				}
			}
		}
	}
}
