#include "Application.h"

int main()
{
	Application* app = Create();
	app->Run();
	delete app;

	return 0;
}