#pragma once

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"

class renderer
{
public:
	renderer();
	~renderer();

	void bg_color(float red, float green, float blue);
	void draw(vertex_array& va, const vertex_buffer& vb, const index_buffer& ib, const shader& sh);
};