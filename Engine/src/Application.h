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
	int width = 1280, height = 720;
	Window window;
	
	bool mouse_follow = false;
	double x, y;
	
	std::vector<double> vertices;
	std::vector<unsigned int> indices;
	unsigned int va = 0, vb = 0, ib = 0;
	Shader shader;
};