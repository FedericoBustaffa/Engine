#pragma once

#include "Engine.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
	void OnEvent(Event& e);
	void OnCloseEvent(CloseEvent& e);

private:
	// window
	Window window;
};