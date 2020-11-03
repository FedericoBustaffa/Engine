#pragma once

#include <string>

#include "Core.h"
#include "Events/Event.h"

struct GLFWwindow;

struct WindowData
{
	int width, height;
	std::string title;
	bool VSync = true;
	EventFn<Event&> callback = nullptr;

	WindowData(int width, int height, std::string title)
		: width(width), height(height), title(title)
	{
	}
};

class Window
{
public:
	Window(int width = 1280, int height = 720, std::string title = "Engine");
	Window(const WindowData& data);
	Window(const Window& window) = delete;
	~Window();

	bool IsOpen() const;
	void Close();
	void OnUpdate() const;
	void VSync(bool enabled);
	void SetRatio(int num, int denom);
	float GetTime() const;
	void SetEventCallback(EventFn<Event&> callback);
	GLFWwindow* GetNativeWindow() const;

private:
	void Init();

private:
	static bool created;

private:
	GLFWwindow* window = nullptr;
	WindowData data;
	bool open = true;
};