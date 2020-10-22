#pragma once

#include "Event.h"
#include "KeyCodes.h"

class KeyEvent : public Event
{
public:
	KeyCode GetKeyCode() const { return keycode; }

protected:
	KeyEvent(KeyCode keycode)
		: keycode(keycode)
	{
	}

	KeyCode keycode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(KeyCode keycode)
		: KeyEvent(keycode) {}

	EVENT_TYPE(KeyPress)
};

class KeyRepeatedEvent : public KeyEvent
{
public:
	KeyRepeatedEvent(KeyCode keycode, int rep_count)
		: KeyEvent(keycode), rep_count(rep_count) {}

	int GetCount() const { return rep_count; }
	EVENT_TYPE(KeyRepeat)

private:
	int rep_count;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(const KeyCode keycode)
		: KeyEvent(keycode) {}

	EVENT_TYPE(KeyRelease)
};
