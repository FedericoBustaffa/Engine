#pragma once

#include <vector>

#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(const Buffer& buffer);
	void AddIndexBuffer(const IndexBuffer& ib);

private:
	uint32_t id;
	std::vector<Buffer> buffers;
	std::vector<IndexBuffer> index_buffers;
};