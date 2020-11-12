#include "Application.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Application::Application()
	: camera(-8.0, 8.0, -4.5, 4.5)
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

	std::vector<glm::vec4> p1_buffer = {
		{ -7.0f, -1.0f, 0.0f, 1.0f },
		{ -7.0f,  1.0f, 0.0f, 1.0f },
		{ -6.5f,  1.0f, 0.0f, 1.0f },
		{ -6.5f, -1.0f, 0.0f, 1.0f }
	};
	
	std::vector<glm::vec4> p2_buffer = {
		{  6.5f, -1.0f, 0.0f, 1.0f },
		{  6.5f,  1.0f, 0.0f, 1.0f },
		{  7.0f,  1.0f, 0.0f, 1.0f },
		{  7.0f, -1.0f, 0.0f, 1.0f }
	};

	std::vector<glm::vec4> ball_buffer = {
		{ -0.2f, -0.2f, 0.0f, 1.0f },
		{ -0.2f,  0.2f, 0.0f, 1.0f },
		{  0.2f,  0.2f, 0.0f, 1.0f },
		{  0.2f, -0.2f, 0.0f, 1.0f }
	};

	p1 = std::make_shared<Player>(p1_buffer);
	p2 = std::make_shared<Player>(p2_buffer);
	ball = std::make_shared<Ball>(ball_buffer);
}

Application::~Application()
{
}

void Application::Run()
{
	while (window.IsOpen())
	{
		// timestep
		ts.UpdateTime();

		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);
		
		// rendering
		PlayersController();
		ball->Move(ts);

		ball->BoundCollision(-4.5, 4.5);
		ball->PlayerCollision(p1, ts);
		ball->PlayerCollision(p2, ts);
		/*if (ball->Point(-8.0, 8.0))
		{
			ball->ResetModel();
			ball->ResetMove();
		}*/

		// p1
		shader->SetUniform4f("u_color", 0.0f, 0.5f, 0.8f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * p1->GetModel());
		shader->Bind();
		Render::DrawIndexed(p1->GetVA());

		// p2
		shader->SetUniform4f("u_color", 0.8f, 0.2f, 0.2f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * p2->GetModel());
		shader->Bind();
		Render::DrawIndexed(p2->GetVA());

		// ball
		shader->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * ball->GetModel());
		shader->Bind();
		Render::DrawIndexed(ball->GetVA());

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

void Application::PlayersController()
{
	if (Input::IsKeyPressed(window, Key::W) && !p1->UpperBoundCollision(4.5))
		p1->MoveUp(ts);
	if (Input::IsKeyPressed(window, Key::S) && !p1->LowerBoundCollision(-4.5))
		p1->MoveDown(ts);
	
	if (Input::IsKeyPressed(window, Key::Up) && !p2->UpperBoundCollision(4.5))
		p2->MoveUp(ts);
	if (Input::IsKeyPressed(window, Key::Down) && !p2->LowerBoundCollision(-4.5))
		p2->MoveDown(ts);
}

