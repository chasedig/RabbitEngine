#include <RBT/Engine.h>
#include <RBT/graphics/Mesh.h>
#include <RBT/components/MeshComponent.h>
#include <RBT/components/RendererComponent.h>
#include <RBT/components/TransformComponent.h>
#include <RBT/components/ColorMaterialComponent.h>
#include <RBT/graphics/AssetLoader.h>

using namespace RBT;

int main()
{
	Engine* engine = new Engine();
	Mesh* mesh;
	mesh = RBT::AssetLoader::LoadMeshFromPath("meshes/teapot.obj");
	mesh->setupMesh();
	std::thread thread([engine, mesh]()
	{
		engine->window->setTitle("Spinning Teapots");
		std::vector<Entity*> models;
		for (int x = 0; x < 10; x++)
		{
			Entity* entity = new Entity();
			engine->world->entities.push_back(entity);
			//MeshComponent* meshComponent = new MeshComponent(mesh);
			MeshComponent* meshComponent = new MeshComponent(mesh);
			entity->SetComponent(meshComponent);
			RendererComponent* rendererComponent = new RendererComponent();
			rendererComponent->doubleSided = true;
			entity->SetComponent(rendererComponent);
			TransformComponent* transform = new TransformComponent();
			transform->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10));
			transform->transform = glm::rotate(transform->transform, (float)glm::radians((float)x*36), glm::vec3(0, 1, 0));
			transform->transform = glm::translate(transform->transform, glm::vec3(0, 0, 10));
			//transform->transform = glm::rotate(transform->transform, (float)glm::radians(180.0), glm::vec3(0, 1, 0));
			//transform->transform = glm::translate(transform->transform, glm::vec3(0, (rand() % 100 + -50) - 5, 0));
			//transform->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -20));
			entity->SetComponent(transform);
			entity->SetComponent(new ColorMaterialComponent(Color(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX))));
			models.push_back(entity);
			//entity->SetComponent(new ColorMaterialComponent(Color::fromRGB(0, 255, 0)));
			//entity->SetComponent(new ColorMaterialComponent(Color::fromRGB(255, 0, 0)));


		}

		while (true)
		{
			for (Entity* model : models)
			{
				TransformComponent* tC = model->GetComponent<TransformComponent>();
				tC->transform = glm::rotate(tC->transform, 0.000001f, glm::vec3(0, 1, 0));
			}
		}
	});
	engine->Run();
	thread.detach();
}