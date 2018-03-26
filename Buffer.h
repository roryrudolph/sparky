#ifndef BUFFER_H_
#define BUFFER_H_

#include <GL/glew.h>

class Buffer
{
public:
	Buffer(GLfloat *data, GLsizei num_elements, GLuint num_components);
	~Buffer();

	void bind() const;
	void unbind() const;

	inline GLuint get_count() const { return m_num_components; }

private:
	GLuint m_id;
	GLuint m_num_components;
};


#endif // BUFFER_H_
