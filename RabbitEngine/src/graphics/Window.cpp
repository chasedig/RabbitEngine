#include "Window.h"

namespace RBT
{

	Window::Window(const char* title, int width, int height)
	{
		this->width = width;
		this->height = height;
		this->title = title;
		this->window = 0;
		this->renderer = NULL;
		this->camera = new Camera(70, 1, 10);
	}

	void Window::Run()
	{
		std::cout << "Initializing window" << std::endl;
		this->init();
		this->loop();
	}


	void Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Unable to initialize GLFW" << std::endl;
			return;
		}

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
		if (this->window == NULL)
		{
			throw "Unable to create the GLFW window";
		}

		glfwSetWindowUserPointer(window, this);

		auto resizeCallbackGLFWInterface = [](GLFWwindow* window, int width, int height)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->WindowResizeCallback(window, width, height);
		};

		auto cursorPositionCallbackGLFWInterface = [](GLFWwindow* window, double xpos, double ypos)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->CursorPositionCallback(window, xpos, ypos);
		};

		glfwSetWindowSizeCallback(window, resizeCallbackGLFWInterface);

		glfwMakeContextCurrent(window);

		glfwShowWindow(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			return;
		}

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		this->renderer = new Renderer(this, camera);
	}

	float Window::getAspectRatio()
	{
		return this->width / this->height;
	}

	void Window::loop()
	{
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, this->width, this->height);
			renderer->Render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	void Window::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		camera->ProcessMouseMovement(this->xpos - xpos, this->ypos - ypos, true);
	}


}