#include "Application.h"

Application::Application()
	: window(1280, 720, "Sandbox")
{
	window.SetEventCallback(BIND(Application::OnEvent));
}

Application::~Application()
{
}

void Application::Run()
{
	while (window.IsOpen())
	{
		// background color
		Render::BackgroundColor(0.07f, 0.07f, 0.07f, 1.0f);

		// event polling
		window.OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<CloseEvent>(BIND(Application::OnCloseEvent));
}

void Application::OnCloseEvent(CloseEvent& e)
{
	window.Close();
}
