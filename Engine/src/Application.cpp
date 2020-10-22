#include "Application.h"
#include "Core.h"
#include "Render/Renderer.h"
#include "Events/WindowEvent.h"

#include <iostream>

#include <GL/glew.h>

Application::Application()
{
	window.SetEventCallback(BIND(Application::OnEvent));
	window.SetRatio(16, 9);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	float vertices[3 * 3] =	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	unsigned int indices[3] = {
		0, 1, 2
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
}

Application::~Application()
{
}

void Application::Run()
{

	// render loop
	while (window.IsOpen())
	{
		// colore sfondo
		Renderer::BackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

		// rendering
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		// cattura eventi
		window.OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<CloseEvent>(BIND(Application::OnCloseEvent));
	dispatcher.Dispatch<ResizeEvent>(BIND(Application::OnResizeEvent));
}

void Application::OnCloseEvent(CloseEvent& e)
{
	std::cout << e.GetName() << std::endl;
	window.Close();
}

void Application::OnResizeEvent(ResizeEvent& e)
{
	std::cout << e.GetWidth() << ", " << e.GetHeight() << std::endl;
}