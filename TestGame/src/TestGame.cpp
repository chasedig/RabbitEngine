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
	mesh = RBT::AssetLoader::LoadMeshFromPath("meshes/suzanne.fbx");
	mesh->setupMesh();
	std::thread thread([engine, mesh]()
	{
		engine->window->setTitle("RabbitEngine DEMO | Triangle Distribution");
		for (int x = 0; x < 5000; x++)
		{
			Entity* entity = new Entity();
			engine->world->entities.push_back(entity);
			//MeshComponent* meshComponent = new MeshComponent(mesh);
			MeshComponent* meshComponent = new MeshComponent(mesh);
			entity->SetComponent(meshComponent);
			entity->SetComponent(new RendererComponent());
			TransformComponent* transform = new TransformComponent();
			transform->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10));
			transform->transform = glm::rotate(transform->transform, (float)glm::radians((float)x), glm::vec3(0, 1, 0));
			transform->transform = glm::translate(transform->transform, glm::vec3(0, 0, 10));
			transform->transform = glm::translate(transform->transform, glm::vec3(0, (rand() % 100 + -50) - 5, 0));
			entity->SetComponent(transform);
			entity->SetComponent(new ColorMaterialComponent(Color(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX))));
		}
	});
	engine->Run();
	thread.detach();
}