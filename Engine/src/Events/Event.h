#pragma once

#include <string>

enum class EventType
{
	None = 0,
	Close, Resize
};

#define EVENT_TYPE(type)\
	virtual EventType GetType() const override { return EventType::type; }\
	virtual std::string GetName() const override { return #type; }

class Event
{
public:
	virtual EventType GetType() const = 0;
	virtual std::string GetName() const = 0;
};
