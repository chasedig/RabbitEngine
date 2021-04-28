#pragma once
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
namespace RBT
{
	class Window; // forward declaration

	class __declspec(dllexport) Renderer
	{
		public:
			std::vector<Mesh*> meshes;
			Renderer(Window* window, Camera* camera);
			void Render();
			Window* window;
			Camera* camera;
		private:
			Shader* shader;
	};
}