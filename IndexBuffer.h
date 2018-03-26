#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer(GLushort *data, GLsizei num_elements);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline GLuint get_count() const { return m_count; }

private:
	GLuint m_id;
	GLuint m_count;
};


#endif // INDEXBUFFER_H_

