#pragma once
#include "core/Window.h"
#include <core/World.h>
#include <core/System.h>
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
	};
}