#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Renderer.h"
#include "Camera.h"
namespace RBT
{
	class __declspec(dllexport) Window
	{
		public:
			Window(const char* title, int width, int height);
			void Run();
			float getAspectRatio();
		private:
			GLFWwindow* window;
			Renderer* renderer;
			Camera* camera;
			int width;
			int height;
			double xpos, ypos = 0;
			const char* title;
			void init();
			void loop();
			void WindowResizeCallback(GLFWwindow* window, int width, int height);
			void CursorPositionCallback(GLFWwindow*, double xpos, double ypos);
	};
}
