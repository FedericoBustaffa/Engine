#include "Application.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Application::Application()
	: window(1280, 720, "Ping Pong"), camera(-8.0, 8.0, -4.5, 4.5)
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

	p1 = std::make_shared<Player>("Player 1", glm::vec2(-6.8f, -0.6f), glm::vec2(-6.5f, 0.6f));
	p2 = std::make_shared<Player>("Player 2", glm::vec2(6.5f, -0.6f), glm::vec2(6.8f, 0.6f));
	
	glm::vec4 center(0.0, 0.0, 0.0, 1.0);
	ball = std::make_shared<Ball>(center, 0.15f);
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
		
		// movements
		Controller();
		ball->Move(ts);

		// Collisions
		ball->BoundCollision(-4.5, 4.5);
		
		if((ball->GetModel() * ball->GetCenter()).x < -5.0)
			ball->PlayerCollision(p1);
		else if((ball->GetModel() * ball->GetCenter()).x > 5.0)
			ball->PlayerCollision(p2);

		// Score
		if (ball->Goal(8.0f))
		{
			p1->IncPoints();
			std::cout << p1->GetName() << ": " << p1->GetPoints() << std::endl;
			std::cout << p2->GetName() << ": " << p2->GetPoints() << std::endl;
			std::cout << std::endl;
		}

		if (ball->Goal(-8.0f))
		{
			p2->IncPoints();
			std::cout << p1->GetName() << ": " << p1->GetPoints() << std::endl;
			std::cout << p2->GetName() << ": " << p2->GetPoints() << std::endl;
			std::cout << std::endl;
		}

		// p1 rendering
		shader->SetUniform4f("u_color", 0.0f, 0.5f, 0.8f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * p1->GetModel());
		shader->Bind();
		Render::DrawIndexed(p1->GetShape());

		// p2 rendering
		shader->SetUniform4f("u_color", 0.8f, 0.2f, 0.2f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * p2->GetModel());
		shader->Bind();
		Render::DrawIndexed(p2->GetShape());

		// ball rendering
		shader->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * ball->GetModel());
		shader->Bind();
		Render::DrawCircle(ball->GetShape());

		
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

	case Key::Space:
		ball->SetXSpeed(7.0f);
		ball->SetYSpeed(7.0f);
		break;

	default:
		break;
	}
}

void Application::Controller()
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