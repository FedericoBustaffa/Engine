#include "Sandbox.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

Sandbox::Sandbox()
	: window(1280, 720, "Sandbox")
{
	window.SetRatio(16, 9);
	window.VSync(true);
}

Sandbox::~Sandbox()
{
	
}

void Sandbox::Run()
{
	float vertices[] = {
		-0.5f, -0.5f,
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(vertices, 8);
	IndexBuffer ib(indices, 6);

	va.Push(2);

	Shader shader("shaders/shader.hlsl");
	shader.SetUniform4f("u_color", 1.0f, 0.5f, 0.5f);
	Renderer engine;

	// game loop
	while (window.Run())
	{
		// background
		engine.BackgroundColor(0.1f, 0.1f, 0.1f);

		// rendering
		engine.Draw(va, vb, ib, shader);

		// events
		window.OnUpdate();
	}
}
