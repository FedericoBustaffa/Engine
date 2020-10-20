#include "Window.h"

#include <iostream>

Window::Window(int width, int height, const std::string& title)
	: window(nullptr), width(width), height(height), title(title)
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
		std::cout << "errore GLEW" << std::endl;
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

bool Window::run() const
{
	return !glfwWindowShouldClose(window);
}

void Window::on_update() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::set_key_callback(void(*key_fun)(GLFWwindow*, int, int, int, int))
{
	glfwSetKeyCallback(window, key_fun);
}