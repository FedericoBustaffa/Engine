#pragma once

#include <memory>

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
	IndexBuffer(int count, unsigned int* data);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	int GetCount() const;

private:
	uint32_t id;
	int count;
};

