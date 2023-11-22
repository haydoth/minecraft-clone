#pragma once
#include <glad/glad.h>

class vertex_array
{
public:
	vertex_array() { glGenVertexArrays(1, &m_handle); }

	void bind() { glBindVertexArray(m_handle); }
	void unbind() { glBindVertexArray(0); }

	unsigned int get_handle() { return m_handle; }
private:
	unsigned int m_handle = 0;
};

class vertex_buffer
{
public:
	vertex_buffer(float vertices[], unsigned int byte_size_of_vertices)
	{ 
		glGenBuffers(1, &m_handle); 

		glBindBuffer(GL_ARRAY_BUFFER, m_handle);
		glBufferData(GL_ARRAY_BUFFER, byte_size_of_vertices, vertices, GL_STATIC_DRAW);
	}

	void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_handle); }
	void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	unsigned int get_handle() { return m_handle; }
private:
	unsigned int m_handle = 0;
};

class index_buffer
{
public:
	index_buffer(unsigned int indices[], unsigned int byte_size_of_vertices)
	{
		glGenBuffers(1, &m_handle);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_size_of_vertices, indices, GL_STATIC_DRAW);
	}
	void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle); }
	void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	unsigned int get_handle() { return m_handle; }
private:
	unsigned int m_handle = 0;
};

class vertex_attribute_array
{
public:
	vertex_attribute_array(int position, int count, int stride, int offset)
	{
		glVertexAttribPointer(
			position,
			count,
			GL_FLOAT,
			GL_FALSE,
			stride * sizeof(float),
			(void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(position);
	}
};