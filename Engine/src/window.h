#pragma once

#include <string>

struct GLFWwindow;

class window
{
public:
	window(int width, int height, const std::string& title);
	~window();

	void set_key_callback(void(*key_fun)(GLFWwindow*, int, int, int, int));
	bool run() const;
	void on_update() const;
	
private:
	GLFWwindow* gl_window;
	int width, height;
	std::string title;
};