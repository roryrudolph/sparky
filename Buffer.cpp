#include "Buffer.h"

Buffer::Buffer(GLfloat *data, GLsizei n, GLuint count)
	: m_count(count)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, n * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_id);
}

void Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
