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
	engine->window->setTitle("TestGame");
	Entity* entity = new Entity();
	engine->world->entities.push_back(entity);
	Mesh* mesh = new Mesh();
	mesh->vertices = { Vertex(glm::vec3(0,0,0), glm::vec3(0,0,1), glm::vec2(0,0)), Vertex(glm::vec3(1,0,0), glm::vec3(0,0,1), glm::vec2(0,0)), Vertex(glm::vec3(1,1,0), glm::vec3(0,0,1), glm::vec2(0,0)) };
	mesh->setupMesh();
	MeshComponent* meshComponent = new MeshComponent(mesh);
	entity->SetComponent(meshComponent);
	entity->SetComponent(new RendererComponent());
	entity->SetComponent(new TransformComponent(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5))));
	engine->Run();
}