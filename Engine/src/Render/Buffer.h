#pragma once

#include "Layout.h"

class Buffer
{
public:
	Buffer(size_t size, void* data);
	~Buffer();

	void Bind() const;
	void Unbind() const;
	void SetLayout(const Layout& layout);
	const Layout& GetLayout() const;

private:
	uint32_t id;
	Layout* layout;
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

