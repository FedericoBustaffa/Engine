#pragma once

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

class Application
{
public:
	Application();
	~Application();
	void Run();
	void Shutdown();
	void OnEvent(Event& e);
	void OnCloseEvent(CloseEvent& e);

private:
	bool running;
	Window* window;
};