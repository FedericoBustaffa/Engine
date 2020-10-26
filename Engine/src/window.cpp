#include "Window.h"
#include "Core.h"
#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool Window::created = false;

Window::Window(int width, int height, std::string title)
	: data(width, height, title)
{
	Init();
}

Window::Window(const WindowData& data)
	:	data(data)
{
	Init();
}

void Window::Init()
{
	if (created)
	{
		std::cout << "Window already exist" << std::endl;
		exit(EXIT_FAILURE);
	}
	created = true;

	if (!glfwInit())
	{
		std::cout << "glfw error" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
	if (!window)
	{
		std::cout << "window error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &this->data);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// setup eventi
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			CloseEvent e;
			data->callback(e);
		});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			ResizeEvent e(width, height);
			data->callback(e);
		});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key);
					data->callback(e);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyRepeatedEvent e(key, 1);
					data->callback(e);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data->callback(e);
					break;
				}
			}
		});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data->callback(e);
					break;
				}
			
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data->callback(e);
					break;
				}
			}
		});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double x_offset, double y_offset)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e(x_offset, y_offset);
			data->callback(e);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e(x, y);
			data->callback(e);
		});
}

Window::~Window()
{
	created = false;
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::IsOpen() const
{
	return open;
}

void Window::Close()
{
	open = false;
	created = false;
}

void Window::OnUpdate() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::VSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	data.VSync = enabled;
}

void Window::SetRatio(int num, int denom)
{
	glfwSetWindowAspectRatio(window, num, denom);
}


void Window::SetEventCallback(EventFn<Event&> callback)
{
	data.callback = callback;
}
