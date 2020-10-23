#pragma once

#include <vector>

#include "Window.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Render/Shader.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

	// eventi
	void OnEvent(Event& e);
	void OnCloseEvent(CloseEvent& e);
	void OnKeyPressedEvent(KeyPressedEvent& e);
	void OnMouseMovedEvent(MouseMovedEvent& e);

private:
	// window
	int width = 640, height = 480;
	Window window;

	// mouse
	bool mouse_follow = false;
	double x, y;
	
	// rendering objects
	double vertices[3 * 3] = {
		-0.3, -0.5, 0.0,
		 0.0,  0.5, 0.0,
		 0.3, -0.5, 0.0
	};
	unsigned int indices[3] = { 0, 1, 2 };
	unsigned int va = 0, vb = 0, ib = 0;
	Shader shader;
};