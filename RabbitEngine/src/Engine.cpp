#include "Engine.h"
#include "World.h"

// SYSTEMS INCLUDE
#include "systems/RendererSystem.h"

RBT::Engine::Engine()
{
	std::cout << "RabbitEngine Starting... \n";
	this->world = new World();
	this->camera = new Camera(70, 1, 10);
	this->window = new Window(camera, "RabbitEngine", 1080, 640);
	this->Run();
}

void RBT::Engine::Run()
{
	this->updateThread = new std::thread([this]() {
		this->window->Run();
		while (!glfwWindowShouldClose(window->window))
		{
			this->Update();
		}
	});
	updateThread->join();
}

void RBT::Engine::Update()
{
	window->Update();
	for (int s = 0; s < this->systems.size(); s++)
	{
		std::cout << "Update" << std::endl;
	}
}

void RBT::Engine::InitializeSystems()
{
	systems.push_back(new RendererSystem(this->window, this->camera));
}
