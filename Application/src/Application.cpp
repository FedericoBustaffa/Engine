#include "Application.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Application::Application()
	: model(1.0), camera(-8.0, 8.0, -4.5, 4.5)
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
	shader->SetUniform4f("u_color", 0.3f, 0.7f, 0.9f, 1.0f);

	// layout
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Float, 4 }
	}));

	triangle = std::make_shared<Triangle>(sizeof(vertices), vertices, layout);
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
		CameraController();
		SquareTransform();

		shader->SetUniformMat4("mvp", camera.GetViewProjection() * model);
		shader->Bind();
		Render::DrawIndexed(triangle->GetVA());

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

void Application::CameraController()
{
	if (Input::IsKeyPressed(window, Key::Left))
		camera_position.x -= camera_speed * ts();
	if (Input::IsKeyPressed(window, Key::Right))
		camera_position.x += camera_speed * ts();
	if (Input::IsKeyPressed(window, Key::Up))
		camera_position.y += camera_speed * ts();
	if (Input::IsKeyPressed(window, Key::Down))
		camera_position.y -= camera_speed * ts();

	if (Input::IsKeyPressed(window, Key::K))
		camera_rotation += camera_rotation_speed * ts();
	if (Input::IsKeyPressed(window, Key::L))
		camera_rotation -= camera_rotation_speed * ts();

	camera.SetPosition(camera_position);
	camera.SetRotation(camera_rotation);
}

void Application::SquareTransform()
{
	if (Input::IsKeyPressed(window, Key::A))
		move.x -= speed * ts();
	if (Input::IsKeyPressed(window, Key::D))
		move.x += speed * ts();
	if (Input::IsKeyPressed(window, Key::W))
		move.y += speed * ts();
	if (Input::IsKeyPressed(window, Key::S))
		move.y -= speed * ts();

	model = glm::translate(glm::mat4(1.0), move);
}
