#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "ImageLoader.h"
#include <FreeImage.h>
#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind() const;
	void unbind() const;

	inline const GLsizei get_width() const { return m_width; }
	inline const GLsizei get_height() const { return m_height; }

private:
	GLuint load();

	std::string m_filepath;
	GLuint m_tid;
	GLsizei m_width, m_height;

};


#endif // TEXTURE_H_
