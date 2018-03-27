#include "Texture.h"

Texture::Texture(const std::string &filepath)
	: m_filepath(filepath)
{
	m_tid = load();
}

Texture::~Texture()
{

}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_tid);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::load()
{
	BYTE *pixels = ImageLoader::load_image(m_filepath.c_str(), &m_width, &m_height);
	if (pixels == NULL)
	{
		printf("ERROR: %s: Could not load image\n", __func__);
		return 0;
	}
	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	// delete[] pixels;

	return result;
}
