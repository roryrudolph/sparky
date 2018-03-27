#include "ImageLoader.h"

BYTE *ImageLoader::load_image(const char *filepath, GLsizei *width, GLsizei *height)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = NULL;

	fif = FreeImage_GetFileType(filepath, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filepath);
	if (fif == FIF_UNKNOWN)
		return (NULL);

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filepath);
	if (! dib)
		return (NULL);

	BYTE *bits = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);
	if (bits == 0 || width == 0 || height == 0)
		return (NULL);

	return (bits);
}
