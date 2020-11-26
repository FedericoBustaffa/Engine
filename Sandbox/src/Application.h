#pragma once

#include "Engine.h"

#include <memory>

class Application
{
public:
	Application();
	~Application();

	void Run();
	void OnEvent(Event& e);
	void OnClose(CloseEvent& e);
	void OnKeyPressed(KeyPressedEvent& e);

private:
	std::unique_ptr<Window> window;
	OrthoCam camera;
	std::shared_ptr<Shader> shader;
	
	// geometry
	std::shared_ptr<Circle> circle;
};