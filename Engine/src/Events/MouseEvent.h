#pragma once

#include "Event.h"
#include "MouseCodes.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y)
		: x(x), y(y)
	{
	}

	float GetX() const { return x; }
	float GetY() const { return y; }
	EVENT_TYPE(MouseMove)

private:
	float x, y;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float x_offset, float y_offset)
		: x_offset(x_offset), y_offset(y_offset) {}

	float GetXOffset() const { return x_offset; }
	float GetYOffset() const { return y_offset; }
	EVENT_TYPE(MouseScroll)

private:
	float x_offset, y_offset;
};

class MouseButtonEvent : public Event
{
public:
	MouseCode GetMouseButton() const { return button; }

protected:
	MouseButtonEvent(MouseCode button)
		: button(button)
	{
	}

	MouseCode button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(MouseCode button)
		: MouseButtonEvent(button)
	{
	}

	EVENT_TYPE(MouseButtonPress)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(MouseCode button)
		: MouseButtonEvent(button)
	{
	}

	EVENT_TYPE(MouseButtonRelease)
};