#include "Engine.h"

// SYSTEMS INCLUDE
#include <graphics/RendererSystem.h>
#include <core/Logger.h>

RBT::Engine::Engine()
{
	Logger::Log("RabbitEngine Starting...");
	this->world = new World();
	this->camera = new Camera(70, 1, 10);
	this->window = new Window(camera, "RabbitEngine", 1080, 640);
	this->window->Run(); // I put it in the run function and I kept getting glGenVertexArrays errors because the window was not yet initialized!
	this->InitializeSystems();
}

void RBT::Engine::Run()
{
	while (!glfwWindowShouldClose(window->window))
	{
		this->Update();
	}
}

void RBT::Engine::Update()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window->getWidth(), window->getHeight());

	for (int s = 0; s < this->systems.size(); s++)
	{
		systems[s]->Update(this->world);
	}

	glfwSwapBuffers(this->window->window);
	glfwPollEvents();
}

void RBT::Engine::InitializeSystems()
{
	systems.push_back(new RendererSystem(this->window, this->camera));
}
