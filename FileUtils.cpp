#include "FileUtils.h"

std::string FileUtils::read_file(const char *filepath)
{
	FILE *fp;
	unsigned long nbytes;
	char *raw;

	if ((fp = fopen(filepath, "r")) == NULL)
	{
		printf("ERROR: Could not open file: %s\n", filepath);
		return "";
	}

	fseek(fp, 0, SEEK_END);
	nbytes = ftell(fp);
	if ((raw = (char *) calloc(1, nbytes)) == NULL)
	{
		fclose(fp);
		return "";
	}
	fseek(fp, 0, SEEK_SET);
	fread(raw, 1, nbytes, fp);
	fclose(fp);

	std::string buf(raw);
	free(raw);
	return (buf);
}
