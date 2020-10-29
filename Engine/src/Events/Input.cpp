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
