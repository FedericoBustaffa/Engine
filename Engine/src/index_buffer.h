#pragma once

class index_buffer
{
public:
	index_buffer(unsigned int* data, unsigned int count);
	~index_buffer();

	void bind() const;
	void unbind() const;
	unsigned int get_count() const;

private:
	unsigned int id, count;
};