#pragma once

#include "Application.h"

class Sandbox : public Application
{
public:
	Sandbox();
	~Sandbox();
	void Run();

private:
	Window window;
};

Application* Create()
{
	return new Sandbox();
}