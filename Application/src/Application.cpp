#include "Application.h"
#include "Core/Core.h"
#include "Graphics/Render.h"
#include "Events/WindowEvent.h"
#include "Events/Input.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Application::Application()
	: camera(-3.0, 3.0, -3.0, 3.0)
{
	window.SetEventCallback(BIND(Application::OnEvent));

	// shader
	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec4 position;
	
		uniform mat4 vp;
		uniform mat4 model;
	
		void main()
		{
			gl_Position = position * vp * model;
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

	// square
	double square[4 * 2] = {
		-0.3, -0.5,
		-0.3,  0.5,
		 0.3,  0.5,
		 0.3, -0.5
	};
	
	squareVA = std::make_shared<VertexArray>();
	squareVB = std::make_shared<Buffer>(sizeof(square), square);
	
	uint32_t square_indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	squareIB = std::make_shared<IndexBuffer>(6, square_indices);
	
	// layout
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Double, 2 }
	}));

	squareVB->SetLayout(layout);
	squareVA->AddBuffer(squareVB);
	squareVA->SetIndexBuffer(squareIB);
}

Application::~Application()
{
}

void Application::Run()
{
	glm::mat4 model(1.0);
	glm::vec3 square_position(0.0);

	while (window.IsOpen())
	{
		// timestep
		ts.UpdateTime();

		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);
		
		// rendering
		Render::BeginScene();

		// CAMERA
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
		shader->SetUniformMat4("vp", camera.GetViewProjection());

		// SQUARE RENDERING
		if (Input::IsKeyPressed(window, Key::A))
			square_position.x -= square_speed * ts();
		if (Input::IsKeyPressed(window, Key::D))
			square_position.x += square_speed * ts();
		if (Input::IsKeyPressed(window, Key::W))
			square_position.y += square_speed * ts();
		if (Input::IsKeyPressed(window, Key::S))
			square_position.y -= square_speed * ts();
		
		model = glm::translate(glm::mat4(1.0), square_position) *
			glm::rotate(glm::mat4(1.0), glm::radians(40.0f), glm::vec3(0, 0, 1));
		shader->SetUniformMat4("model", model);
		shader->Bind();
		Render::DrawIndexed(squareVA);
		
		Render::EndScene();

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
