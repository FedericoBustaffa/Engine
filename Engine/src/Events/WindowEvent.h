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
	
	EVENT_TYPE(Resize)

private:
	int width, height;
};