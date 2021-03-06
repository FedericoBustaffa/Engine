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
	Window window;
	OrthoCam camera;
	TimeStep ts;

	std::shared_ptr<Shader> shader;

	glm::vec3 move;
};