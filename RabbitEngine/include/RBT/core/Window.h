#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <RBT/graphics/Camera.h>
namespace RBT
{
	class Window
	{
		public:
			Window(Camera* camera, const char* title, int width, int height);
			void Run();
			float getAspectRatio();
			int getWidth();
			int getHeight();
			GLFWwindow* window;
			void setTitle(const char* title) { this->title = title; glfwSetWindowTitle(this->window, this->title); }
			void setDimensions(int width, int height) { this->width = width; this->height = height; glfwSetWindowSize(this->window, this->width, this->height); }
		private:
			Camera* camera;
			int width;
			int height;
			double cursor_xpos = 0;
			double cursor_ypos = 0;
			bool cursor_set = false;
			const char* title;
			void init();
			void WindowResizeCallback(GLFWwindow* window, int width, int height);
			void CursorPositionCallback(GLFWwindow*, double xpos, double ypos);
	};
}
