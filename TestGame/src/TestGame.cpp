#include <Engine.h>
#include <graphics/Mesh.h>
#include <components/MeshComponent.h>
#include <components/RendererComponent.h>
#include <components/TransformComponent.h>
#include <windows.h>

using namespace RBT;

int main()
{
	Engine* engine = new Engine();
	engine->window->setTitle("RabbitEngine DEMO | Triangle Distribution");
	Mesh* mesh = new Mesh();
	mesh->vertices = { Vertex(glm::vec3(0,0,0), glm::vec3(0,0,1), glm::vec2(0,0)), Vertex(glm::vec3(1,0,0), glm::vec3(0,0,1), glm::vec2(0,0)), Vertex(glm::vec3(1,1,0), glm::vec3(0,0,1), glm::vec2(0,0)) };
	mesh->setupMesh();
	for (int x = 0; x < 20000; x++)
	{
		Entity* entity = new Entity();
		engine->world->entities.push_back(entity);
		MeshComponent* meshComponent = new MeshComponent(mesh);
		entity->SetComponent(meshComponent);
		entity->SetComponent(new RendererComponent());
		TransformComponent* transform = new TransformComponent();
		transform->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10));
		transform->transform = glm::rotate(transform->transform, (float)glm::radians((float)x), glm::vec3(0, 1, 0));
		transform->transform = glm::translate(transform->transform, glm::vec3(0, 0, 10));
		transform->transform = glm::translate(transform->transform, glm::vec3(0, (rand() % 50 + -25) - 5, 0));
		entity->SetComponent(transform);
	}
	engine->Run();
}