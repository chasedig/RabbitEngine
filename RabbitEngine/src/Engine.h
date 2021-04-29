#pragma once
#include "graphics/Window.h"
#include "World.h"
#include "systems/System.h"
#include <thread>

namespace RBT
{
	class Engine
	{
		public:
			Engine();
			void Run();
			void Update();
			std::vector<System*> systems;
			Window* window;
			World* world;
			Camera* camera;
		private:
			void InitializeSystems();
			std::thread* updateThread;
	};
}