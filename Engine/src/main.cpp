#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"
#include "window.h"
#include "renderer.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	window test_window(1280, 720, "Test OpenGL");
	test_window.set_key_callback(key_callback);

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

	vertex_array va;
	vertex_buffer vb(vertices, 8);
	index_buffer ib(indices, 6);

	va.push(2);

	shader sh("shaders/shader.hlsl");
	sh.set_uniform4f("u_color", 1.0f, 0.5f, 0.5f);
	renderer engine;
	
	// game loop
	while (test_window.run())
	{
		// background
		engine.bg_color(0.1f, 0.1f, 0.1f);
		
		// rendering
		engine.draw(va, vb, ib, sh);

		// events
		test_window.on_update();
	}

	return 0;
}