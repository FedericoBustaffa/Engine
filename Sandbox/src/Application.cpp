#include "Application.h"

#include <iostream>
#include <vector>

Application::Application()
	: camera(-1.0, 1.0, -1.0, 1.0)
{
	window = std::make_unique<Window>(1280, 720, "Sandbox");
	window->SetEventCallback(BIND(Application::OnEvent));
	
	// shader
	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec4 position;
	
		uniform mat4 mvp;
	
		void main()
		{
			gl_Position = position * mvp;
		}
	)";

	std::string fragment_src = R"(
		#version 330 core

		out vec4 color;
		uniform vec4 u_color;

		void main()
		{
			color = u_color;
		}
	)";
	shader = std::make_shared<Shader>(vertex_src, fragment_src);

	// square setup
	glm::vec2 bottom_left;
	bottom_left.x = 0.0f;
	bottom_left.y = 0.0f;
	square = std::make_shared<Square>(bottom_left, 0.5f);
	square->SetColor(0.0f, 0.5f, 0.8f, 1.0f);

	// triangle setup
	std::vector<glm::vec2> t_vertices = {
		{ -0.5f, -0.5f },
		{ -0.5f,  0.0f },
		{  0.0f, -0.5f }
	};

	triangle = std::make_shared<Triangle>(t_vertices);
	triangle->SetColor(7.0f, 0.5f, 0.2f, 1.0f);
}

Application::~Application()
{
}

void Application::Run()
{
	while (window->IsOpen())
	{
		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		// drawing
		shader->SetUniform4f("u_color", square->GetColor());
		shader->SetUniformMat4("mvp", camera.GetViewProjection());
		shader->Bind();
		Render::DrawIndexed(square->GetVA());

		shader->SetUniform4f("u_color", triangle->GetColor());
		shader->SetUniformMat4("mvp", camera.GetViewProjection());
		shader->Bind();
		Render::DrawIndexed(triangle->GetVA());

		// event polling
		window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<CloseEvent>(BIND(Application::OnClose));
	dispatcher.Dispatch<KeyPressedEvent>(BIND(Application::OnKeyPressed));
}

void Application::OnClose(CloseEvent& e)
{
	window->Close();
}

void Application::OnKeyPressed(KeyPressedEvent& e)
{
	switch (e.GetKeyCode())
	{
	case Key::Enter:
		window->Close();
		break;
	
	default:
		break;
	}
}