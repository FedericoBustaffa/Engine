#include "Application.h"
#include "Core.h"
#include "Graphics/Render.h"
#include "Events/WindowEvent.h"
#include "Events/Input.h"

#include <iostream>

Application::Application()
{
	window.SetEventCallback(BIND(Application::OnEvent));

	// shader
	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec4 v_position;
		
		void main()
		{
			gl_Position = v_position;
		}
	)";

	std::string fragment_src = R"(
		#version 330 core

		out vec4 color;

		void main()
		{
			color = vec4(0.8, 0.3, 0.1, 1.0);
		}
	)";

	shader = std::make_shared<Shader>(vertex_src, fragment_src);

	// buffers
	double vertices[3 * 2] = {
		-0.5, -0.5,
		 0.0,  0.5,
		 0.5, -0.5
	};
	
	uint32_t indices[3] = { 0, 1, 2 };
	
	va = std::make_shared<VertexArray>();
	vb = std::make_shared<Buffer>(sizeof(vertices), vertices);
	ib = std::make_shared<IndexBuffer>(3, indices);

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
	double x, y;

	// render loop
	while (window.IsOpen())
	{
		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		// rendering
		Render::BeginScene();

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
