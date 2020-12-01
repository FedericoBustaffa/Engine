#pragma once

#include <functional>

// puntatore a funzioni membro
#define BIND(fn) std::bind(&fn, this, std::placeholders::_1)

// colori
#define BLACK		{ 0.0f, 0.0f, 0.0f, 1.0f }
#define WHITE		{ 1.0f, 1.0f, 1.0f, 1.0f }
#define DARK_GREY	{ 0.07f, 0.07f, 0.07f, 1.0f }
#define RED			{ 1.0f, 0.0f, 0.0f, 1.0f }
#define GREEN		{ 0.0f, 1.0f, 0.0f, 1.0f }
#define BLUE		{ 0.0f, 0.0f, 1.0f, 1.0f }
