#pragma once

#include <vector>

#include "Window.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
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
	void OnResizeEvent(ResizeEvent& e);

private:
	Window window;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int va = 0, vb = 0, ib = 0;
	Shader shader;
};