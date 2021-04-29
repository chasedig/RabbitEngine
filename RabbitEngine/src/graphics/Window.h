#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Camera.h"
namespace RBT
{
	class Window
	{
		public:
			Window(Camera* camera, const char* title, int width, int height);
			void Run();
			void Update();
			float getAspectRatio();
			GLFWwindow* window;
			void setTitle(const char* title) { this->title = title; }
			void setDimensions(int width, int height) { this->width = width; this->height = height; }
		private:
			Camera* camera;
			int width;
			int height;
			double xpos = 0;
			double ypos = 0;
			const char* title;
			void init();
			void WindowResizeCallback(GLFWwindow* window, int width, int height);
			void CursorPositionCallback(GLFWwindow*, double xpos, double ypos);
	};
}
