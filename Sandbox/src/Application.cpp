#include "Application.h"

#include <iostream>
#include <vector>

Application::Application()
	: camera(-8.0, 8.0, -4.5, 4.5)
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

	// circle
	circle = std::make_shared<Circle>({ 0.0f, 0.0f }, 5.0f);
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

		// polygon
		shader->SetUniformMat4("mvp", camera.GetViewProjection());
		shader->SetUniform4f("u_color", circle->GetColor());
		shader->Bind();
		Render::DrawIndexed(poly->GetVA());

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