#pragma once

#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void EnableLayout(const Buffer& buffer);

private:
	uint32_t id;
};