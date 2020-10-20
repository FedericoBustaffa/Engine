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

	// eventi
	void SetKeyCB(void(*key_fn)(GLFWwindow*, int, int, int, int));
	void SetWindowCloseCB(void(*close_fn)(GLFWwindow*));
	
private:
	GLFWwindow* window;
	int width, height;
	std::string title;
	bool running;
};