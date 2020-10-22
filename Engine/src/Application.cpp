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

	vertices = {
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, vertices.data(), GL_STATIC_DRAW);

	indices = { 0, 1, 2 };
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	shader.SetUniform4f("u_color", 0.8f, 0.6f, 0.2f);
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
		vertices[4] += 0.0001f;
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, vertices.data(), GL_STATIC_DRAW);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		// event polling
		window.OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<CloseEvent>(BIND(Application::OnCloseEvent));
}

void Application::OnCloseEvent(CloseEvent& e)
{
	window.Close();
}