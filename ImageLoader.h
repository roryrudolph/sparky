#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <string>
#include <FreeImage.h>
#include <GL/glew.h>

class ImageLoader
{
public:
	static BYTE *load_image(const char *filepath, GLsizei *width, GLsizei *height);
};


#endif // IMAGELOADER_H_
