#include <RBT/core/Window.h>

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
		glfwSetCursorPosCallback(window, cursorPositionCallbackGLFWInterface);

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

		glfwSetWindowSizeLimits(window, 800, 500, GLFW_DONT_CARE, GLFW_DONT_CARE);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	}

	float Window::getAspectRatio()
	{
		return (float)this->width / (float)this->height; // Cast to float! Damn integer division is at it again...
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
		if (cursor_set == true)
		{
			camera->ProcessMouseMovement(xpos - this->cursor_xpos, ypos - this->cursor_ypos, true);
		}
		else
		{
			cursor_set = true;
		}
		this->cursor_xpos = xpos;
		this->cursor_ypos = ypos;
	}

	void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		if (severity == GL_DEBUG_SEVERITY_HIGH)
		{
			std::cout << message << std::endl;
		}
	}


}