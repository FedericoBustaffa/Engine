#pragma once

#include "Event.h"
#include "MouseCodes.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(double x, double y)
		: x(x), y(y)
	{
	}

	double GetX() const { return x; }
	double GetY() const { return y; }
	EVENT_TYPE(MouseMove)

private:
	double x, y;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(double x_offset, double y_offset)
		: x_offset(x_offset), y_offset(y_offset) {}

	double GetXOffset() const { return x_offset; }
	double GetYOffset() const { return y_offset; }
	EVENT_TYPE(MouseScroll)

private:
	double x_offset, y_offset;
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