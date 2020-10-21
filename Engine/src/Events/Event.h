#pragma once

#include <string>

enum class EventType
{
	None = 0,
	Close
};

class Event
{
public:
	virtual ~Event() = default;
	virtual std::string GetName() const = 0;
	virtual EventType GetType() const = 0;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& e)
		: to_handle(e)
	{
	}

	template <typename T, typename F>
	void Dispatch(const F& func)
	{

	}

private:
	Event& to_handle;
};