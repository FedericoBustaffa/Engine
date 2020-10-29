#include "Input.h"

#include <GLFW/glfw3.h>

bool Input::IsKeyPressed(const Window& window, KeyCode keycode)
{
	GLFWwindow* native = window.GetNativeWindow();
	int state = glfwGetKey(native, keycode);
	if (state == GLFW_PRESS || state == GLFW_REPEAT)
		return true;
	return false;
}

bool Input::IsKeyReleased(const Window& window, KeyCode keycode)
{
	GLFWwindow* native = window.GetNativeWindow();
	int state = glfwGetKey(native, keycode);
	if (state == GLFW_RELEASE)
		return true;
	return false;
}

bool Input::IsMouseButtonPressed(const Window& window, MouseCode button)
{
	GLFWwindow* native = window.GetNativeWindow();
	int state = glfwGetMouseButton(native, button);
	if (state == GLFW_PRESS || state == GLFW_REPEAT)
		return true;
	return false;
}

bool Input::IsMouseButtonReleased(const Window& window, MouseCode button)
{
	GLFWwindow* native = window.GetNativeWindow();
	int state = glfwGetMouseButton(native, button);
	if (state == GLFW_RELEASE)
		return true;
	return false;
}

double Input::GetMouseX(const Window& window)
{
	GLFWwindow* native = window.GetNativeWindow();
	double x;
	glfwGetCursorPos(native, &x, nullptr);

	return x;
}

double Input::GetMouseY(const Window& window)
{
	GLFWwindow* native = window.GetNativeWindow();
	double y;
	glfwGetCursorPos(native, nullptr, &y);

	return y;
}
