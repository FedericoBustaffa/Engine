#include "Application.h"

#include <iostream>

Application::Application()
{
	if (!glfwInit())
	{
		std::cout << "glfw error" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Application::~Application()
{
	glfwTerminate();
}