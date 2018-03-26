#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_buffers.size(); ++i)
		delete m_buffers;
}

void VertexArray::addBuffer(Buffer *bufer, GLuint index)
{
	buffer->bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index,
		buffer->get_count(),
	GL_FLOAT,
	GL_FALSE, 0, 0);
	buffer->unbind();
}