#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
	for (size_t i = 0; i < m_buffers.size(); ++i)
		delete m_buffers[i];
}

void VertexArray::addBuffer(Buffer *buffer, GLuint index)
{
	this->bind();
	buffer-> bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(
		index,               // Layout location
		buffer->get_count(),
		GL_FLOAT,            // Data type
		GL_FALSE,            // Normalize
		0,                   // Stride
		0                    // Pointer
	);
	buffer->unbind();
	this->unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
