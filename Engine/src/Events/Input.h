#pragma once

#include "Window.h"
#include "KeyCodes.h"

class Input
{
public:
	static bool IsKeyPressed(const Window& window, KeyCode keycode);
	static bool IsKeyReleased(const Window& window, KeyCode keycode);

private:
	Input() = default;
};