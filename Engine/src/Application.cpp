#include "Application.h"
#include "Core.h"
#include "Render/Renderer.h"
#include "Events/WindowEvent.h"

#include <iostream>
#include <GL/glew.h>

Application::Application()
	: shader("shaders/shader.hlsl")
{
	window.SetEventCallback(BIND(Application::OnEvent));
	window.SetRatio(16, 9);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	float vertices[3 * 3] =	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int indices[3] = { 0, 1, 2 };
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	shader.SetUniform4f("u_color", 0.5f, 0.8f, 0.0f);
}

Application::~Application()
{
}

void Application::Run()
{

	// render loop
	while (window.IsOpen())
	{
		// background color
		Renderer::BackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

		// rendering
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		// event polling
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