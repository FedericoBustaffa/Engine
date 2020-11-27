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

	std::shared_ptr<Circle> circle;
	float speed = 10.0f;
	glm::vec3 move;
};