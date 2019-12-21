#include "mainHeader.h"


char* GetFileExtension(char * file_name)
{
	int file_name_len = strlen(file_name);
	file_name += file_name_len;

	char *file_ext;
	for (int i = 0; i < file_name_len; i++)
	{
		if (*file_name == '.')
		{
			file_ext = file_name + 1;
			break;
		}
		file_name--;
	}
	return file_ext;
}
