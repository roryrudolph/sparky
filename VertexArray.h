#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "Buffer.h"
#include <GL/glew.h>
#include <vector>

class VertexArray
{
public:
	VertexArray(GLushort *data, GLsizei n, GLuint count);
	~VertexArray();

	void addBuffer(Buffer *bufer, GLuint index);

private:
	GLuint m_id;
	std::vector <Buffer *> m_buffers;
};


#endif // VERTEXARRAY_H_

