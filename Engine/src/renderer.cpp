#include "renderer.h"

#include <GL/glew.h>

renderer::renderer()
{
}

renderer::~renderer()
{
}

void renderer::bg_color(float red, float green, float blue)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red, green, blue, 1.0f);
}

void renderer::draw(vertex_array& va, const vertex_buffer& vb, const index_buffer& ib, const shader& sh)
{
	va.bind();
	vb.bind();
	va.enable();
	sh.bind();
	glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
	va.disable();
}