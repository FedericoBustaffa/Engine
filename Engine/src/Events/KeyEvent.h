#pragma once

#include "Event.h"

class KeyEvent : public Event
{

};

class KeyPressedEvent : public KeyEvent
{

};

class KeyRepeatedEvent : public KeyEvent
{

};

class KeyReleasedEvent : public KeyEvent
{

};