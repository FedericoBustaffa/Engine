#pragma once

#include "Core/Window.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

class Input
{
public:
	static bool IsKeyPressed(const Window& window, KeyCode keycode);
	static bool IsKeyReleased(const Window& window, KeyCode keycode);

	static bool IsMouseButtonPressed(const Window& window, MouseCode button);
	static bool IsMouseButtonReleased(const Window& window, MouseCode button);
	static double GetMouseX(const Window& window);
	static double GetMouseY(const Window& window);

private:
	Input() = default;
};