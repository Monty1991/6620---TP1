#include "string.h"

#include <stdlib.h>

#define STRING_INITIAL_SIZE 16

// Resizes a string.
// Returns STRING_SUCCESS on success
// STRING_ERROR on failure
int stringResize(String_t *string, unsigned int new_size);

const char *stringC_str(String_t *string) {
	if (!string)
		return NULL;

	return string->data;
}

int stringCreate(String_t *string) {
	if (!string)
		return STRING_ERROR;

	char *data = (char *) malloc(sizeof(char) * STRING_INITIAL_SIZE);
	if (!data)
		return STRING_ERROR;

	*data = '\0';

	string->data = data;
	string->size = 1;
	string->capacity = STRING_INITIAL_SIZE;
	
	return STRING_SUCCESS;
}

void stringDestroy(String_t *string) {
	if (!string)
		return;

	if (string->data) {
		free(string->data);
		string->data = NULL;
		string->size = 0;
		string->capacity = 0;
	}
}

int stringPush_back(String_t *string, char c) {
	if (!string)
		return STRING_ERROR;

	if (string->size >= string->capacity) {
		if (stringResize(string, string->capacity * 2) == STRING_ERROR)
			return STRING_ERROR;
	}

	string->data[string->size - 1] = c;
	string->data[string->size++] = '\0';
	
	return STRING_SUCCESS;
}

int stringResize(String_t *string, unsigned int new_size) {
	char *new_data = (char *) realloc(string->data, sizeof(char) * new_size);
	if (!new_data)
		return STRING_ERROR;

	string->data = new_data;
	string->capacity = new_size;

	return STRING_SUCCESS;
}

char *stringStrip(String_t *string) {
	if (!string)
		return NULL;

	// reduces the lenght of the string. Note size includes null terminator.
	char *data = (char *) realloc(string->data, sizeof(char) * string->size);
	string->data = NULL;
	string->size = 0;
	string->capacity = 0;

	return data;
}
