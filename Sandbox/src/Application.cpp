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

	std::vector<glm::vec2> vertices = {
		{ -0.1f, -0.1f },
		{ -0.1f,  0.1f },
		{  0.1f,  0.1f },
		{  0.1f, -0.1f }
	};
	quad = std::make_shared<Quad>(vertices);
	quad->SetColor(0.2f, 0.7f, 0.2f, 1.0f);
}

Application::~Application()
{
}

void Application::Run()
{
	glm::vec4 bottom_left, top_right;

	while (window.IsOpen())
	{
		ts.UpdateTime();

		// background color
		Render::BackgroundColor(DARK_GREY);

		// drawing
		bottom_left = quad->GetVertex(0);
		top_right = quad->GetVertex(2);

		if (bottom_left.x <= -8.0 || top_right.x >= 8.0)
			x_speed *= -1;
		if (bottom_left.y <= -4.5 || top_right.y >= 4.5)
			y_speed *= -1;

		move.x += x_speed * ts();
		move.y += y_speed * ts();
		quad->SetModel(glm::translate(glm::mat4(1.0), move));

		shader->SetUniformMat4("mvp", camera.GetViewProjection() * quad->GetModel());
		shader->SetUniform4f("u_color", quad->GetColor());
		shader->Bind();
		Render::DrawPolygon(quad);

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