#include "Application.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "Render/Renderer.h"

Application::Application()
	: running(true), window(nullptr)
{
	if (!glfwInit())
	{
		std::cout << "glfw error" << std::endl;
		exit(EXIT_FAILURE);
	}

	WindowData data(1280, 720, "Application");
	window = new Window(data);
}

Application::~Application()
{
	delete window;
	glfwTerminate();
}

void Application::Run()
{
	while (running)
	{
		Renderer::BackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
		window->OnUpdate();
	}
}

void Application::Shutdown()
{
	running = false;
}

void Application::OnEvent(Event& e)
{
	
}

void Application::OnCloseEvent(CloseEvent& e)
{
	running = false;
}