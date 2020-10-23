#include "Application.h"
#include "Core.h"
#include "Render/Renderer.h"
#include "Events/WindowEvent.h"

#include <iostream>
#include <GL/glew.h>

Application::Application()
	: window(width, height), shader("shaders/shader.hlsl")
{
	window.SetEventCallback(BIND(Application::OnEvent));
	window.SetRatio(16, 9);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	vertices = {
		-0.3, -0.5, 0.0,
		 0.0,  0.5, 0.0,
		 0.3, -0.5, 0.0
	};
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, vertices.data(), GL_DYNAMIC_DRAW);

	indices = { 0, 1, 2 };
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, indices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), nullptr);
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
		if (mouse_follow)
		{
			vertices[3] = (x - (width / 2)) / (width / 2);
			vertices[4] = ((height / 2) - y) / (height / 2);
		}
		
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_DYNAMIC_DRAW);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		// event polling
		window.OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<CloseEvent>(BIND(Application::OnCloseEvent));
	dispatcher.Dispatch<KeyPressedEvent>(BIND(Application::OnKeyPressedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND(Application::OnMouseMovedEvent));
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

	case Key::Space:
		mouse_follow = !mouse_follow;
		break;

	default:
		break;
	}
}

void Application::OnMouseMovedEvent(MouseMovedEvent& e)
{
	x = e.GetX();
	y = e.GetY();
}
