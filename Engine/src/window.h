#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct WindowData
{
	int width, height;
	std::string title;
	bool VSync;

	WindowData(int width, int height, std::string title)
		: width(width), height(height), title(title),
		VSync(true)
	{
	}
};

class Window
{
public:
	Window(const WindowData& data);
	~Window();

	void OnUpdate() const;
	void VSync(bool enabled);
	void SetRatio(int num, int denom);

private:
	static bool created;

private:
	GLFWwindow* window;
	WindowData data;
};