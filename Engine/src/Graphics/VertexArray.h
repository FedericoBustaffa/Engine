#pragma once

#include <memory>

#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void SetBuffer(const std::shared_ptr<Buffer>& buffer);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);
	size_t GetIndexCount() const;

private:
	uint32_t id;
	std::shared_ptr<Buffer> buffer;
	std::shared_ptr<IndexBuffer> index_buffer;
};