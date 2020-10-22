#pragma once

#include "Window.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

	// eventi
	void OnEvent(Event& e);
	void OnCloseEvent(CloseEvent& e);
	void OnResizeEvent(ResizeEvent& e);

private:
	Window window;

	unsigned int va = 0, vb = 0, ib = 0;
};