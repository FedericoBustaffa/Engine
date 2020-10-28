#include "Application.h"
#include "Core.h"
#include "Render/Renderer.h"
#include "Events/WindowEvent.h"

#include <iostream>
#include <GL/glew.h>

Application::Application()
{
	window.SetEventCallback(BIND(Application::OnEvent));

	double vertices[4 * 7] = {
		// position			// color
		-0.5, -0.5, 0.0,	0.4, 0.8, 0.2, 1.0,
		-0.5,  0.5, 0.0,	0.4, 0.8, 0.2, 1.0,
		 0.5,  0.5, 0.0,	0.4, 0.8, 0.2, 1.0,
		 0.5, -0.5, 0.0,	0.4, 0.8, 0.2, 1.0
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<Buffer> vb = std::make_shared<Buffer>(sizeof(vertices), vertices);
	std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(6, indices);
	
	// layout
	std::shared_ptr<Layout> layout;
	layout.reset(new Layout({
		{ "position", ShaderType::Double3 },
		{ "color", ShaderType::Double4 }
	}));

	vb->SetLayout(layout);
	va->AddBuffer(vb);

	// shader
	std::string vertex_source = R"(
		#version 330 core

		layout(location = 0) in vec4 v_position;
		layout(location = 1) in vec4 v_color;
		
		out vec4 f_color;

		void main()
		{
			f_color = v_color;
			gl_Position = v_position;
		}
	)";

	std::string fragment_source = R"(
		#version 330 core

		in vec4 f_color;
		out vec4 color;

		void main()
		{
			color = f_color;
		}
	)";

	shader = std::make_shared<Shader>(vertex_source, fragment_source);
}

Application::~Application()
{
}

void Application::Run()
{
	// render loop
	while (window.IsOpen())
	{
		// background color
		Renderer::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);
		
		// rendering
		va->Bind();
		shader->Bind();
		glDrawElements(GL_TRIANGLES, va->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

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
