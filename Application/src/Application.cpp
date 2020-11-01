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

		layout(location = 0) in vec4 v_position;
	
		uniform mat4 view;
		uniform mat4 transform;
	
		void main()
		{
			gl_Position = view * transform * v_position;
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
	glm::mat4 view = glm::ortho(-1.0, 1.0, -1.0, 1.0);
	shader->SetUniformMat4("view", view);

	// buffers
	double vertices[4 * 2] = {
		-0.5, -0.5,
		-0.5,  0.5,
		 0.5,  0.5,
		 0.5, -0.5
	};
	
	uint32_t indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	
	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(sizeof(vertices), vertices);
	ib = std::make_shared<IndexBuffer>(6, indices);

	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Double, 2 }
	}));

	vb->SetLayout(layout);
	va->AddBuffer(vb);
	va->SetIndexBuffer(ib);
}

Application::~Application()
{
}

void Application::Run()
{
	glm::vec3 position(0.0f);
	
	while (window.IsOpen())
	{
		// timestep
		ts.UpdateTime();

		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		
		// rendering
		Render::BeginScene();

		if (Input::IsKeyPressed(window, Key::A))
			position.x -= 5.0f * ts.GetSeconds();
		else if (Input::IsKeyPressed(window, Key::D))
			position.x += 5.0f * ts.GetSeconds();
		
		if (Input::IsKeyPressed(window, Key::W))
			position.y += 5.0f * ts.GetSeconds();
		else if (Input::IsKeyPressed(window, Key::S))
			position.y -= 5.0f * ts.GetSeconds();
		
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

		shader->SetUniformMat4("transform", transform);
		shader->Bind();
		Render::DrawIndexed(va);

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
