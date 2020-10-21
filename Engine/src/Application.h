#pragma once

#include "Window.h"

class Application
{
public:
	Application();
	virtual ~Application();
	virtual void Run() = 0;
};

Application* Create();