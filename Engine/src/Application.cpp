#include "Application.h"
#include "Core.h"
#include "Render/Renderer.h"
#include "Events/WindowEvent.h"

#include <iostream>
#include <GL/glew.h>

Application::Application()
{
	window.SetEventCallback(BIND(Application::OnEvent));

	double vertices[4 * 3] = {
		-0.5, -0.5, 0.0,
		-0.5,  0.5, 0.0,
		 0.5,  0.5, 0.0,
		 0.5, -0.5, 0.0
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	// vertex array
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	// vertex buffer
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// index buffer
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// attributes
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), nullptr);
	glEnableVertexAttribArray(0);

	// shader
	std::string vertex_source = R"(
		#version 330 core

		layout(location = 0) in vec4 v_position;
		out vec4 v_color;
		
		void main()
		{
			v_color = v_position;
			gl_Position = v_position;
		}
	)";

	std::string fragment_source = R"(
		#version 330 core

		in vec4 v_color;
		out vec4 color;

		void main()
		{
			color = v_color;
		}
	)";

	shader = new Shader(vertex_source, fragment_source);

	// GPU info
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
}

Application::~Application()
{
	glDeleteVertexArrays(1, &va);
	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);
	delete shader;
}

void Application::Run()
{
	// render loop
	while (window.IsOpen())
	{
		// background color
		Renderer::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);
		
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
