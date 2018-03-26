#ifndef BUFFER_H_
#define BUFFER_H_

#include <GL/glew.h>

class Buffer
{
public:
	Buffer(GLfloat *data, GLsizei n, GLuint count);
	~Buffer();

	void bind() const;
	void unbind() const;

	inline GLuint get_count() const { return m_count; }

private:
	GLuint m_id;
	GLuint m_count;
};


#endif // BUFFER_H_
