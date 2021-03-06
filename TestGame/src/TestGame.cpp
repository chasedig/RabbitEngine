#include <RBT/Engine.h>
#include <RBT/graphics/Mesh.h>
#include <RBT/components/MeshComponent.h>
#include <RBT/components/RendererComponent.h>
#include <RBT/components/TransformComponent.h>
#include <RBT/components/ColorMaterialComponent.h>
#include <RBT/graphics/AssetLoader.h>
#include <RBT/core/Entity.h>
#include <RBT/core/Entity.h>
#include <RBT/components/PointLightComponent.h>

using namespace RBT;

int main()
{
	Engine* engine = new Engine();
	Mesh* teapot_mesh;
	teapot_mesh = RBT::AssetLoader::LoadMeshFromPath("meshes/teapot.fbx");
	teapot_mesh->setupMesh();
	Mesh* cube_mesh;
	cube_mesh = RBT::AssetLoader::LoadMeshFromPath("meshes/cube.fbx");
	cube_mesh->setupMesh();
	std::thread thread([engine, teapot_mesh, cube_mesh]()
	{
		engine->window->setTitle("Spinning Teapots");

		std::vector<Entity*> models;
		for (int x = 0; x < 10; x++)
		{
			Entity* entity = new Entity();
			engine->world->AddEntity(entity);
			//MeshComponent* meshComponent = new MeshComponent(mesh);
			MeshComponent* meshComponent;
			meshComponent = new MeshComponent(teapot_mesh);
			entity->SetComponent(meshComponent);
			RendererComponent* rendererComponent = new RendererComponent();
			rendererComponent->doubleSided = true;
			entity->SetComponent(rendererComponent);
			TransformComponent* transform = new TransformComponent();
			transform->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -50));
			transform->transform = glm::rotate(transform->transform, (float)glm::radians((float)x*36), glm::vec3(0, 1, 0));
			transform->transform = glm::translate(transform->transform, glm::vec3(0, 0, 50));
			Entity* light = new Entity();
			engine->world->AddEntity(light);
			Color lightColor = Color(1,1,1);
			if (x % 3 == 0)
			{
				lightColor = Color(1, 0, 0);
			}
			else if (x % 2 == 0)
			{
				lightColor = Color(0, 1, 0);
			}
			else
			{
				lightColor = Color(0, 0, 1);
			}
			light->SetComponent(new RendererComponent());
			light->SetComponent(new MeshComponent(cube_mesh));
			light->SetComponent(new ColorMaterialComponent(lightColor));
			light->SetComponent(new PointLightComponent(lightColor, 20.0f));
			light->SetComponent(new TransformComponent(glm::translate(transform->transform, glm::vec3(0.0f, 10.0f, 0.0f))));
			//transform->transform = glm::rotate(transform->transform, (float)glm::radians(180.0), glm::vec3(0, 1, 0));
			//transform->transform = glm::translate(transform->transform, glm::vec3(0, (rand() % 100 + -50) - 5, 0));
			//transform->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -20));
			entity->SetComponent(transform);
			//entity->SetComponent(new ColorMaterialComponent(Color(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX))));
			models.push_back(entity);
			entity->SetComponent(new ColorMaterialComponent(Color::fromRGB(255, 255, 255)));
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

	return 0;
}