#pragma once

#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct WindowData
{
	int width, height;
	std::string title;
	bool VSync;

	WindowData(int width = 1280, int height = 720, std::string title = "Engine")
		: width(width), height(height), title(title),
		VSync(true)
	{
	}
};

class Window
{
private:
	Window(const WindowData& data);
	Window(const Window& window) = delete;
	~Window();

public:
	bool IsOpen() const;
	void Close();
	void OnUpdate() const;
	void VSync(bool enabled);
	void SetRatio(int num, int denom);

public:
	static Window* Create(const WindowData& data);

private:
	static bool created;

private:
	GLFWwindow* window;
	WindowData data;
	bool open;
};