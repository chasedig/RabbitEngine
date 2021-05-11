#include <RBT/graphics/RendererSystem.h>
#include "glad/glad.h"
#include <RBT/core/Window.h>
#include <RBT/components/MeshComponent.h>
#include <RBT/components/RendererComponent.h>
#include <RBT/components/TransformComponent.h>
#include <RBT/components/ColorMaterialComponent.h>
#include <RBT/components/PointLightComponent.h>
#include <RBT/core/Entity.h>
#include <algorithm>
namespace RBT
{

	const int MAX_LIGHTS = 16;

	float GetEntityDistanceFromEntity(Entity* e0, Entity* e1);

	RendererSystem::RendererSystem(Window* window, Camera* camera)
	{
		this->window = window;
		this->camera = camera;
		this->colorShader = new Shader("vertex.glsl", "colorMaterial_frag.glsl");
	}

	void RendererSystem::Update(World* world)
	{
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, window->getWidth(), window->getHeight());

		glCullFace(GL_BACK);

		Shader* shader = NULL;


		glm::mat4 projectionMatrix = glm::perspective(camera->FOV, window->getAspectRatio(), camera->near, camera->far);

		glm::mat4 viewMatrix = camera->getViewMatrix();

		std::vector<PointLightComponent*> pointLights = world->GetComponentsOfType<PointLightComponent>();

		for (Entity* entity : world->entities)
		{
			RendererComponent* renderer = entity->GetComponent<RendererComponent>();
			MeshComponent* meshComponent = entity->GetComponent<MeshComponent>();
			TransformComponent* transform = entity->GetComponent<TransformComponent>();
			ColorMaterialComponent* colorMaterial = entity->GetComponent<ColorMaterialComponent>();


			std::vector<PointLightComponent*> closestPointLights = std::vector<PointLightComponent*>(pointLights);
			std::sort(closestPointLights.begin(), closestPointLights.end(), [entity](PointLightComponent* i, PointLightComponent* j)
			{
				return GetEntityDistanceFromEntity(i->entity, entity) < GetEntityDistanceFromEntity(j->entity, entity);
			});


			if (renderer && meshComponent && transform)
			{
				if (renderer->enabled == true)
				{
					if (colorMaterial)
					{
						shader = colorShader;
						if (shader)
						{
							shader->bind();
						}
						shader->setVec3Uniform("color", glm::vec3(colorMaterial->color.R, colorMaterial->color.G, colorMaterial->color.B));
					}

					if (shader)
					{
						shader->setMat4Uniform("projection", projectionMatrix);
						shader->setMat4Uniform("view", viewMatrix);

						Mesh mesh = *meshComponent->mesh;
						glm::mat4 modelMatrix = transform->transform;
						shader->setMat4Uniform("model", modelMatrix);

						// Lighting
						int pointLightCount = (int)std::min((int)MAX_LIGHTS, (int)closestPointLights.size());

						for (int p = 0; p < pointLightCount; p++)
						{
							PointLightComponent* pointLight = closestPointLights[p];
							TransformComponent* pointLightTransform = pointLight->entity->GetComponent<TransformComponent>();
							if (pointLightTransform)
							{
								std::string pointLightIndexAccess = "pointLights[" + std::to_string(p) + "]";
								shader->setVec3Uniform(pointLightIndexAccess + ".position", pointLightTransform->transform[3]);
								shader->setVec3Uniform(pointLightIndexAccess + ".color", glm::vec3(pointLight->color.R, pointLight->color.G, pointLight->color.B));
								shader->setFloatUniform(pointLightIndexAccess + ".power", pointLight->power);
							}
						}

						if (renderer->doubleSided == false)
						{
							glEnable(GL_CULL_FACE);
						}
						else
						{
							glDisable(GL_CULL_FACE);
						}

						glBindVertexArray(mesh.VAO);
						//glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.vertices.size());
						glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
						glBindVertexArray(0);

						shader->unbind();
					}
				}
			}
		}
	}

	float GetEntityDistanceFromEntity(Entity* e0, Entity* e1)
	{
		return glm::length(e0->GetComponent<TransformComponent>()->transform[3] - e1->GetComponent<TransformComponent>()->transform[3]);
	}
}
