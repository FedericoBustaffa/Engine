#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	Window window(1280, 720, "Test OpenGL");
	window.VSync(true);
	window.SetKeyCB(key_callback);

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

	return 0;
}