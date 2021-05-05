#pragma once
#include "RBT/core/Window.h"
#include "RBT/core/World.h"
#include "RBT/core/System.h"
#include <thread>

namespace RBT
{
	class Engine
	{
		public:
			Engine();
			void Run();
			std::vector<System*> systems;
			Window* window;
			World* world;
			Camera* camera;
			float deltaTick = 0;
		private:
			void InitializeSystems();
			void Update();
	};
}