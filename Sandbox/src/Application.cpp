#include "Application.h"

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Application::Application()
	: window(1280, 720, "Ping Pong"), camera(-640.0, 640.0, -360.0, 360.0), move(0.0)
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

	glm::vec2 center = { 0.0f, 0.0f };
	circle = std::make_shared<Circle>(center, 200.0f);
	circle->SetColor(RED);
}

Application::~Application()
{
}

void Application::Run()
{
	while (window.IsOpen())
	{
		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		// drawing
		if (Input::IsKeyPressed(window, Key::A))
		{
			move.x += speed * ts();
			circle->SetModel(glm::translate(glm::mat4(1.0), move));
		}

		if (Input::IsKeyPressed(window, Key::D))
		{
			move.x -= speed * ts();
			circle->SetModel(glm::translate(glm::mat4(1.0), move));
		}

		shader->SetUniformMat4("mvp", camera.GetViewProjection() * circle->GetModel());
		shader->SetUniform4f("u_color", circle->GetColor());
		shader->Bind();
		Render::DrawCircle(circle);

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