#pragma once

#include <functional>

// puntatore a funzioni membro
#define BIND(fn) std::bind(&fn, this, std::placeholders::_1)
