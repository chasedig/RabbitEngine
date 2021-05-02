#pragma once
#include <vector>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Camera.h>
#include <core/World.h>
#include <core/System.h>

namespace RBT
{
	class Window; // forward declaration

	class RendererSystem : public System
	{
		public:
			RendererSystem(Window* window, Camera* camera);
			void Update(World* world);
			Window* window;
			Camera* camera;
		private:
			Shader* colorShader;
	};
}