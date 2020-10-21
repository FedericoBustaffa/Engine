#include "Window.h"

#include <iostream>

bool Window::created = false;

Window::Window(const WindowData& data)
	:	window(nullptr),
		data(data)
{
	if (created)
	{
		std::cout << "Window already exist" << std::endl;
		exit(EXIT_FAILURE);
	}

	created = true;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
	if (!window)
	{
		std::cout << "window error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &this->data);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// eventi
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
	{
		std::cout << "close" << std::endl;
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
	});
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::OnUpdate() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::VSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	data.VSync = enabled;
}

void Window::SetRatio(int num, int denom)
{
	glfwSetWindowAspectRatio(window, num, denom);
}