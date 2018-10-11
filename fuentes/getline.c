#include "getline.h"

#include <stdlib.h>
#define INITIAL_SIZE 16

int getline(String_t *str, FILE *file_in)
{
	if (!file_in || !str)
		return GETLINE_ERROR;

	if (feof(file_in))
		return GETLINE_ERROR;

	int c;
	while (!feof(file_in)) {
		c = fgetc(file_in);
		if (c == '\n')
			break;

		if (STRING_ERROR == stringPush_back(str, c)) {
			stringDestroy(str);
			return GETLINE_ERROR;
		}
	}

	return GETLINE_SUCCESS;
}
