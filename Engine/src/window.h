#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void set_key_callback(void(*key_fun)(GLFWwindow*, int, int, int, int));
	bool run() const;
	void on_update() const;
	
private:
	GLFWwindow* window;
	int width, height;
	std::string title;
};