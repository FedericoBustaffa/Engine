#pragma once

#include "Event.h"

class CloseEvent : public Event
{
public:
	EVENT_TYPE(Close)
};

class ResizeEvent : public Event
{
public:
	ResizeEvent(int width, int height)
		: width(width), height(height)
	{
	}

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	EVENT_TYPE(Resize)

private:
	int width, height;
};