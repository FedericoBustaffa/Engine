#include "Application.h"

#include <iostream>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

Application::Application()
	: window(1280, 720, "Sandbox"), camera(-8.0, 8.0, -4.5, 4.5), move(0.0)
{
	window.SetEventCallback(BIND(Application::OnEvent));
	
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

	glm::vec2 square_bottom_left(0, 3.0);
	square = std::make_shared<Square>(square_bottom_left, 1.0f);
	square->SetColor(0.2f, 0.7f, 0.2f, 1.0f);
}

Application::~Application()
{
}

void Application::Run()
{
	while (window.IsOpen())
	{
		ts.UpdateTime();

		// background color
		Render::BackgroundColor(DARK_GREY);

		// drawing
		if ((square->GetModel() * square->GetBottomLeft()).y <= -8.0)
			init_speed *= -1;
		speed = init_speed - gravity * ts.GetTime();
		init_speed = speed;
		move.y += speed;
		square->SetModel(glm::translate(glm::mat4(1.0), move));

		shader->SetUniformMat4("mvp", camera.GetViewProjection() * square->GetModel());
		shader->SetUniform4f("u_color", square->GetColor());
		shader->Bind();
		Render::DrawPolygon(square);

		// event polling
		window.OnUpdate();
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
	window.Close();
}

void Application::OnKeyPressed(KeyPressedEvent& e)
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