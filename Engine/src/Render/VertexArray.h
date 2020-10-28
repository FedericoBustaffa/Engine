#pragma once

#include <memory>
#include <vector>

#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);
	void AddBuffer(const std::shared_ptr<Buffer>& buffer);
	int GetIndexCount() const;

private:
	uint32_t id;
	std::vector<std::shared_ptr<Buffer>> buffers;
	std::shared_ptr<IndexBuffer> index_buffer;
};