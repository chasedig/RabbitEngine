#pragma once
#include <vector>
#include <RBT/graphics/Mesh.h>
#include <RBT/graphics/Shader.h>
#include <RBT/graphics/Camera.h>
#include <RBT/core/World.h>
#include <RBT/core/System.h>

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