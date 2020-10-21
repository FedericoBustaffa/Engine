#include "Window.h"

int main()
{
	Window* window = Window::Create(WindowData());
	window->SetRatio(16, 9);
	window->VSync(true);

	while (window->IsOpen())
	{
		window->OnUpdate();
	}
	
	return 0;
}