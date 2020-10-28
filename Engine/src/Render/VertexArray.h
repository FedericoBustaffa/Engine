#pragma once

#include <vector>
#include <memory>

#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(const Buffer& buffer);
	void SetIndexBuffer(const IndexBuffer& ib);

private:
	uint32_t id;
	std::vector<Buffer> buffers;
	IndexBuffer* index_buffer;
};