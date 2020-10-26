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

	// vertex array
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	// vertex buffer
	vb = new Buffer(sizeof(vertices), vertices);

	// index buffer
	ib = new IndexBuffer(6, indices);

	// attributes
	BufferLayout layout({
		{ "position", ShaderType::Double3 },
		{ "color", ShaderType::Double4 }
	});

	vb->SetLayout(layout);

	int index = 0;
	for (const auto& elem : layout)
	{
		glVertexAttribPointer(index, elem.Get, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), nullptr);
		glEnableVertexAttribArray(index);
		index++;
	}


	void* offset = (void*)(3 * sizeof(double));
	glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), offset);
	glEnableVertexAttribArray(1);

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

	shader = new Shader(vertex_source, fragment_source);
}

Application::~Application()
{
	glDeleteVertexArrays(1, &va);
	delete vb;
	delete ib;
	delete shader;
}

void Application::Run()
{
	// GPU info
	std::cout << "Vendor: " << Renderer::GetVendor() << std::endl;
	std::cout << "Renderer: " << Renderer::GetRenderer() << std::endl;

	// render loop
	while (window.IsOpen())
	{
		// background color
		Renderer::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);
		
		// rendering
		glBindVertexArray(va);
		shader->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
