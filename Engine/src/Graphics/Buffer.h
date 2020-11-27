#pragma once

#include <memory>
#include <vector>

#include "Layout.h"

class Buffer
{
public:
	Buffer(size_t size, void* data);
	~Buffer();

	void Bind() const;
	void Unbind() const;
	void SetLayout(const std::shared_ptr<Layout>& layout);
	const std::shared_ptr<Layout>& GetLayout() const;

private:
	uint32_t id;
	std::shared_ptr<Layout> layout;
};


class IndexBuffer
{
public:
	IndexBuffer(size_t count, unsigned int* indices);
	IndexBuffer(const std::vector<unsigned int>& indices);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	size_t GetCount() const;

private:
	uint32_t id;
	size_t count;
};

