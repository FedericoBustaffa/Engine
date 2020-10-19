#include "window.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

window::window(int width, int height, const std::string& title)
	: gl_window(nullptr), width(width), height(height), title(title)
{
	if (!glfwInit())
	{
		std::cout << "glfw error" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	gl_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!gl_window)
	{
		std::cout << "window error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(gl_window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "errore GLEW" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwGetFramebufferSize(gl_window, &width, &height);
	glViewport(0, 0, width, height);
}

window::~window()
{
	glfwDestroyWindow(gl_window);
	glfwTerminate();
}

bool window::run() const
{
	return !glfwWindowShouldClose(gl_window);
}

void window::on_update() const
{
	glfwSwapBuffers(gl_window);
	glfwPollEvents();
}

void window::set_key_callback(void(*key_fun)(GLFWwindow*, int, int, int, int))
{
	glfwSetKeyCallback(gl_window, key_fun);
}