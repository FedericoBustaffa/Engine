#pragma once

#include <iostream>
#include <functional>
#include <GL/glew.h>

#ifdef DBG
#define CALL(x)\
	while (glGetError() != GL_NO_ERROR);\
	x;\
	unsigned int err;\
	while(err = glGetError(){\
		std::cout << "OpenGL error: " << err << std::endl;\
	}
#else
#define CALL(x)
#endif

// puntatore a funzioni membro
#define BIND(fn) std::bind(&fn, this, std::placeholders::_1)
