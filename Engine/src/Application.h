#pragma once

#include <vector>

#include "Window.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

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

	// metodi privati
private:
	

private:
	// window
	Window window;

	// rendering objects
	double vertices[4 * 3] = {
		-0.1, -0.1, 0.0,
		-0.1,  0.1, 0.0,
		 0.1,  0.1, 0.0,
		 0.1, -0.1, 0.0
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int va = 0, vb = 0, ib = 0;
};