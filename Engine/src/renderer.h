#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void BackgroundColor(float red, float green, float blue);
	void Draw(VertexArray& va, const VertexBuffer& vb, const IndexBuffer& ib, const Shader& shader);
};