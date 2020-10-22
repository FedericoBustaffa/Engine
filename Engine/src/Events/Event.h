#pragma once

#include <string>

enum class EventType
{
	None = 0,
	Close, Resize,
	KeyPress, KeyRepeat, KeyRelease,
	MouseMove, MouseScroll, MouseButtonPress, MouseButtonRelease
};

#define EVENT_TYPE(type)\
	static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetType() const override { return GetStaticType(); }\
	virtual std::string GetName() const override { return #type; }

class Event
{
public:
	virtual EventType GetType() const = 0;
	virtual std::string GetName() const = 0;
};

template <typename T>
using EventFn = std::function<void(T&)>;

class EventDispatcher
{
public:
	EventDispatcher(Event& e)
		: to_handle(e)
	{
	}

	template <typename T, typename F>
	void Dispatch(const F& callback)
	{
		if (to_handle.GetType() == T::GetStaticType())
			callback(static_cast<T&>(to_handle));
	}

private:
	Event& to_handle;
};