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
		{ -7.5f, -1.0f, 0.0f, 1.0f },
		{ -7.5f,  1.0f, 0.0f, 1.0f },
		{ -6.5f,  1.0f, 0.0f, 1.0f },
		{ -6.5f, -1.0f, 0.0f, 1.0f }
	};
	
	std::vector<glm::vec4> p2_buffer = {
		{  6.5f, -1.0f, 0.0f, 1.0f },
		{  6.5f,  1.0f, 0.0f, 1.0f },
		{  7.5f,  1.0f, 0.0f, 1.0f },
		{  7.5f, -1.0f, 0.0f, 1.0f }
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	p1 = std::make_shared<Player>(p1_buffer, indices);
	p2 = std::make_shared<Player>(p2_buffer, indices);
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

		if (Collision())
			std::cout << "collisione" << std::endl;

		// p1
		shader->SetUniform4f("u_color", 0.4f, 0.8f, 0.2f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * p1->GetModel());
		shader->Bind();
		Render::DrawIndexed(p1->GetVA());

		// p2
		shader->SetUniform4f("u_color", 0.8f, 0.2f, 0.2f, 1.0f);
		shader->SetUniformMat4("mvp", camera.GetViewProjection() * p2->GetModel());
		shader->Bind();
		Render::DrawIndexed(p2->GetVA());

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
	if (Input::IsKeyPressed(window, Key::W) && !UpperBoundCollision(p1))
		p1->MoveUp(ts);
	if (Input::IsKeyPressed(window, Key::S) && !LowerBoundCollision(p1))
		p1->MoveDown(ts);
	
	if (Input::IsKeyPressed(window, Key::I) && !UpperBoundCollision(p2))
		p2->MoveUp(ts);
	if (Input::IsKeyPressed(window, Key::K) && !LowerBoundCollision(p2))
		p2->MoveDown(ts);
}

bool Application::Collision()
{
	std::vector<glm::vec4> vertices = p1->GetVertices();
	glm::vec4 bottom_left = p2->GetModel() * p2->GetVertices()[0];
	glm::vec4 top_right = p2->GetModel() * p2->GetVertices()[2];

	for (auto& vertex : vertices)
	{
		vertex = p1->GetModel() * vertex;

		if (vertex.x >= bottom_left.x && vertex.x <= top_right.x)
		{
			if (vertex.y >= bottom_left.y && vertex.y <= top_right.y)
				return true;
		}
	}

	return false;
}

bool Application::UpperBoundCollision(const std::shared_ptr<Player>& player)
{
	glm::vec4 top_right = player->GetModel() * player->GetVertices()[2];
	return top_right.y > 4.5;
}

bool Application::LowerBoundCollision(const std::shared_ptr<Player>& player)
{
	glm::vec4 bottom_left = player->GetModel() * player->GetVertices()[0];
	return bottom_left.y < -4.5;
}
