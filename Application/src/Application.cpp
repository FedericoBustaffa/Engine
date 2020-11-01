#include "Application.h"
#include "Core/Core.h"
#include "Graphics/Render.h"
#include "Events/WindowEvent.h"
#include "Events/Input.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Application::Application()
{
	window.SetEventCallback(BIND(Application::OnEvent));

	// shader
	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec4 position;
	
		uniform mat4 proj;
		uniform mat4 model;
	
		void main()
		{
			gl_Position = position * proj * model;
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
	
	glm::mat4 proj = glm::ortho(-2.0, 2.0, -2.0, 2.0);
	shader->SetUniformMat4("proj", proj);

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
	glm::vec3 position(0.0);
	float speed = 1.0f;

	while (window.IsOpen())
	{
		// timestep
		ts.UpdateTime();

		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		
		// rendering
		Render::BeginScene();

		// SQUARE RENDERING
		if (Input::IsKeyPressed(window, Key::A))
			position.x -= speed * ts();
		if (Input::IsKeyPressed(window, Key::D))
			position.x += speed * ts();

		if (Input::IsKeyPressed(window, Key::W))
			position.y += speed * ts();
		if (Input::IsKeyPressed(window, Key::S))
			position.y -= speed * ts();

		model = glm::translate(glm::mat4(1.0), position);
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
