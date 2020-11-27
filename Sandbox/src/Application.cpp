#include "Application.h"

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

	std::vector<glm::vec2> t = {
		{ -3.0f, -2.0f },
		{  0.0f,  2.0f },
		{  3.0f, -2.0f }
	};
	
	std::vector<glm::vec2> r = {
		{ -3.0f, -2.0f },
		{ -3.0f,  2.0f },
		{  3.0f,  2.0f },
		{  3.0f, -2.0f }
	};

	triangle = std::make_shared<Triangle>(t);
	triangle->SetColor(RED);

	rectangle = std::make_shared<Quad>(r);
	rectangle->SetColor(BLUE);
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
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		// drawing
		if (Input::IsKeyPressed(window, Key::A))
		{
			move.x -= speed * ts();
			triangle->SetModel(glm::translate(glm::mat4(1.0), move));
		}

		if (Input::IsKeyPressed(window, Key::D))
		{
			move.x += speed * ts();
			triangle->SetModel(glm::translate(glm::mat4(1.0), move));
		}

		shader->SetUniformMat4("mvp", camera.GetViewProjection() * rectangle->GetModel());
		shader->SetUniform4f("u_color", rectangle->GetColor());
		shader->Bind();
		Render::DrawIndexed(rectangle);
		
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * triangle->GetModel());
		shader->SetUniform4f("u_color", triangle->GetColor());
		shader->Bind();
		Render::DrawIndexed(triangle);


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