#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "Buffer.h"
#include <GL/glew.h>
#include <vector>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(Buffer *buffer, GLuint index);
	void bind() const;
	void unbind() const;
private:
	GLuint m_id;
	std::vector<Buffer *> m_buffers;
};


#endif // VERTEXARRAY_H_

