#pragma once

#include "Event.h"

class CloseEvent : public Event
{
	std::string GetName() const override
	{
		return "CloseEvent";
	}
};