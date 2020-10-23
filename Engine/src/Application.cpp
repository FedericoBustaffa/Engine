#include "Application.h"
#include "Core.h"
#include "Render/Renderer.h"
#include "Events/WindowEvent.h"

#include <iostream>
#include <GL/glew.h>

Application::Application()
{
	window.SetEventCallback(BIND(Application::OnEvent));

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), nullptr);
	glEnableVertexAttribArray(0);
}

Application::~Application()
{
	glDeleteVertexArrays(1, &va);
	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);
}

void Application::Run()
{
	// render loop
	while (window.IsOpen())
	{
		// background color
		Renderer::BackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
		
		// rendering
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		// event polling
		window.OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<CloseEvent>(BIND(Application::OnCloseEvent));
	dispatcher.Dispatch<KeyPressedEvent>(BIND(Application::OnKeyPressedEvent));
}

void Application::OnCloseEvent(CloseEvent& e)
{
	window.Close();
}

void Application::OnKeyPressedEvent(KeyPressedEvent& e)
{
	switch (e.GetKeyCode())
	{
	case Key::Enter:
		window.Close();
		break;

	default:
		break;
	}
}
