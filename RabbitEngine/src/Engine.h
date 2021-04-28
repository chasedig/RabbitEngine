#pragma once
#include <graphics/Window.h>

namespace RBT
{
	class __declspec(dllexport) Engine
	{
		public:
			Engine(Window* window);
			Window* window;
	};
}