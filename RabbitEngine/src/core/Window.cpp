#include "Window.h"

namespace RBT
{

	void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	Window::Window(Camera* camera, const char* title, int width, int height)
	{
		this->width = width;
		this->height = height;
		this->title = title;
		this->window = 0;
		this->camera = camera;
	}

	void Window::Run()
	{
		std::cout << "Initializing window" << std::endl;
		this->init();
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

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debugMessage, NULL);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	}

	float Window::getAspectRatio()
	{
		return this->width / this->height;
	}

	int Window::getWidth()
	{
		return this->width;
	}

	int Window::getHeight()
	{
		return this->height;
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

	void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		std::cout << message << std::endl;
	}


}