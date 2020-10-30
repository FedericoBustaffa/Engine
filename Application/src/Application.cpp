#include "Application.h"
#include "Core.h"
#include "Graphics/Render.h"
#include "Events/WindowEvent.h"
#include "Events/Input.h"

#include <iostream>

Application::Application()
{
	window.SetEventCallback(BIND(Application::OnEvent));

	// triangle
	double triangle[3 * 2] = {
		-0.8, -0.5,
		-0.5,  0.5,
		-0.2, -0.5
	};

	unsigned int triangle_ind[3] = { 0, 1, 2 };

	triangle_va = std::make_shared<VertexArray>();
	triangle_vb = std::make_shared<Buffer>(sizeof(triangle), triangle);
	triangle_ib = std::make_shared<IndexBuffer>(3, triangle_ind);
	
	std::shared_ptr<Layout> triangle_lay;
	triangle_lay.reset(new Layout({
		{ "triangle", ShaderType::Double, 2 }
	}));

	triangle_vb->SetLayout(triangle_lay);
	triangle_va->AddBuffer(triangle_vb);
	triangle_va->SetIndexBuffer(triangle_ib);

	// square
	double square[4 * 2] = {
		 0.2, -0.5,
		 0.2,  0.5,
		 0.8,  0.5,
		 0.8, -0.5
	};

	unsigned int square_ind[6] = {
		0, 1, 2,
		2, 3, 0
	};

	square_va = std::make_shared<VertexArray>();
	square_vb = std::make_shared<Buffer>(sizeof(square), square);
	square_ib = std::make_shared<IndexBuffer>(6, square_ind);

	std::shared_ptr<Layout> square_lay;
	square_lay.reset(new Layout({
		{ "square", ShaderType::Double, 2 }
	}));

	square_vb->SetLayout(square_lay);
	square_va->AddBuffer(square_vb);
	square_va->SetIndexBuffer(square_ib);

	// shader
	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec4 v_position;
		
		void main()
		{
			gl_Position = v_position;
		}
	)";

	std::string red_fragment_src = R"(
		#version 330 core

		out vec4 color;

		void main()
		{
			color = vec4(0.8, 0.3, 0.1, 1.0);
		}
	)";
	
	std::string blue_fragment_src = R"(
		#version 330 core

		out vec4 color;

		void main()
		{
			color = vec4(0.1, 0.3, 0.8, 1.0);
		}
	)";

	red_shader = std::make_shared<Shader>(vertex_src, red_fragment_src);
	blue_shader = std::make_shared<Shader>(vertex_src, blue_fragment_src);
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
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		// polling
		if (Input::IsKeyPressed(window, Key::G))
		{
			std::cout << Input::GetMouseX(window) << ", " << std::flush;
			std::cout << Input::GetMouseY(window) << std::endl;
		}
		
		// rendering
		Render::BeginScene();

		red_shader->Bind();
		Render::DrawIndexed(triangle_va);

		blue_shader->Bind();
		Render::DrawIndexed(square_va);

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
