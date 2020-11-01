#include "Application.h"
#include "Core/Core.h"
#include "Graphics/Render.h"
#include "Events/WindowEvent.h"
#include "Events/Input.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Application::Application()
	: camera(-2.0, 2.0, -2.0, 2.0)
{
	window.SetEventCallback(BIND(Application::OnEvent));

	// shader
	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec4 position;
	
		uniform mat4 proj;
		uniform mat4 model;
		uniform mat4 view;
	
		void main()
		{
			gl_Position = position * proj * model * view;
		}
	)";

	std::string fragment_src = R"(
		#version 330 core

		out vec4 color;

		void main()
		{
			color = vec4(0.4, 0.75, 0.2, 1.0);
		}
	)";

	shader = std::make_shared<Shader>(vertex_src, fragment_src);
	
	shader->SetUniformMat4("proj", camera.GetProjection());

	// square
	double square[4 * 2] = {
		-0.8, -0.5,
		-0.8,  0.5,
		-0.2,  0.5,
		-0.2, -0.5
	};
	
	squareVA = std::make_shared<VertexArray>();
	squareVB = std::make_shared<Buffer>(sizeof(square), square);
	
	uint32_t square_indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	squareIB = std::make_shared<IndexBuffer>(6, square_indices);
	
	
	// triangle
	double triangle[3 * 2] = {
		 0.2, -0.5,
		 0.5,  0.5,
		 0.8, -0.5
	};

	triangleVA = std::make_shared<VertexArray>();
	triangleVB = std::make_shared<Buffer>(sizeof(triangle), triangle);

	uint32_t triangle_indices[3] = { 0, 1, 2 };

	triangleIB = std::make_shared<IndexBuffer>(3, triangle_indices);

	// layout
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Double, 2 }
	}));

	squareVB->SetLayout(layout);
	squareVA->AddBuffer(squareVB);
	squareVA->SetIndexBuffer(squareIB);
	
	triangleVB->SetLayout(layout);
	triangleVA->AddBuffer(triangleVB);
	triangleVA->SetIndexBuffer(triangleIB);
}

Application::~Application()
{
}

void Application::Run()
{
	glm::mat4 model(1.0);
	glm::vec3 square_position(0.0);
	glm::vec3 camera_position(0.0);

	while (window.IsOpen())
	{
		// timestep
		ts.UpdateTime();

		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		
		// rendering
		Render::BeginScene();

		// CAMERA
		if (Input::IsKeyPressed(window, Key::Right))
			camera_position.x += camera_speed * ts();
		if (Input::IsKeyPressed(window, Key::Left))
			camera_position.x -= camera_speed * ts();

		if (Input::IsKeyPressed(window, Key::Up))
			camera_position.y += camera_speed * ts();
		if (Input::IsKeyPressed(window, Key::Down))
			camera_position.y -= camera_speed * ts();

		camera.SetPosition(camera_position);
		// TODO fix camera
		glm::mat4 view = glm::inverse(glm::translate(glm::mat4(1.0), camera_position));
		shader->SetUniformMat4("view", view);

		// SQUARE RENDERING
		if (Input::IsKeyPressed(window, Key::A))
			square_position.x -= square_speed * ts();
		if (Input::IsKeyPressed(window, Key::D))
			square_position.x += square_speed * ts();

		if (Input::IsKeyPressed(window, Key::W))
			square_position.y += square_speed * ts();
		if (Input::IsKeyPressed(window, Key::S))
			square_position.y -= square_speed * ts();

		model = glm::translate(glm::mat4(1.0), square_position);
		shader->SetUniformMat4("model", model);
		
		shader->Bind();
		Render::DrawIndexed(squareVA);

		// TRIANGLE RENDERING
		shader->SetUniformMat4("model", glm::mat4(1.0));
		shader->Bind();
		Render::DrawIndexed(triangleVA);

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
