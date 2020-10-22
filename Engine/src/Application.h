#pragma once

#include <functional>

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

class Application
{
public:
	Application()
	{
		window.SetRatio(16, 9);
		window.SetEventCallback(BIND(Application::OnEvent));
	}
	
	~Application()
	{
	}

	void Run()
	{
		while (window.IsOpen())
		{
			window.OnUpdate();
		}
	}

	void OnEvent(Event& e)
	{
		std::cout << e.GetName() << std::endl;
		if (e.GetType() == EventType::Close)
			window.Close();
	}

private:
	Window window;
};