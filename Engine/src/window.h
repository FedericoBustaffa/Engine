#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	bool Run() const;
	void OnUpdate() const;
	void VSync(bool enabled);
	void SetRatio(int num, int denom);

private:
	GLFWwindow* window;
	int width, height;
	std::string title;
	bool running;
};