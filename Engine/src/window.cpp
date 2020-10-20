#include "Window.h"

#include <iostream>

Window::Window(int width, int height, const std::string& title)
	: window(nullptr), width(width), height(height), title(title),
	running(true)
{
	if (!glfwInit())
	{
		std::cout << "glfw error" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window)
	{
		std::cout << "window error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::Run() const
{
	return running;
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
}

// Eventi
void Window::SetKeyCB(void(*key_fn)(GLFWwindow*, int, int, int, int))
{
	glfwSetKeyCallback(window, key_fn);
}

void Window::SetWindowCloseCB(void(*close_fn)(GLFWwindow*))
{
	glfwSetWindowCloseCallback(window, close_fn);
}