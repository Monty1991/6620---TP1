#include "text.h"

#define TEXT_INITIAL_SIZE 16

// remove definition of stdlib
#define qsort(...) asdf(__VA_ARGS__)
#include <stdlib.h>
#undef qsort

#include "getline.h"
#include "string.h"
#include "qsort.h"

// Adds a line to text
// Returns TEXT_SUCCESS on success
// TEXT_ERROR on failure.
int textAddLine(Text_t *text, String_t *str);

// Resizes a text.
// Returns TEXT_SUCCESS on success
// TEXT_ERROR on failure.
int textResize(Text_t *text, unsigned int new_size);

int textAddLine(Text_t *text, String_t *str) {
	if (text->size >= text->capacity) {
		if (textResize(text, text->capacity * 2) == TEXT_ERROR)
			return TEXT_ERROR;
	}

	text->data[text->size++] = stringStrip(str);

	return TEXT_SUCCESS;
}

int textCreate(Text_t *text) {
	if (!text)
		return TEXT_ERROR;

	char **data = (char **) malloc(sizeof(char *) * TEXT_INITIAL_SIZE);
	if (!data)
		return TEXT_ERROR;

	text->data = data;
	text->size = 0;
	text->capacity = TEXT_INITIAL_SIZE;
	
	return TEXT_SUCCESS;
}

void textDestroy(Text_t *text) {
	if (!text)
		return;

	if (text->data) {
		for (int i = 0; i < text->size; i++)
			free(text->data[i]);
		free(text->data);
		text->data = NULL;
		text->size = 0;
		text->capacity = 0;
	}
}

int textRead(Text_t *text, FILE *file) {
	if (!file || !text)
		return TEXT_ERROR;

	String_t string;
	while (!feof(file)) {
		if (stringCreate(&string) == STRING_ERROR)
			return TEXT_ERROR;

		if (getline(&string, file) == GETLINE_ERROR) {
			stringDestroy(&string);
			return TEXT_ERROR;
		}

		if (textAddLine(text, &string) == STRING_ERROR) {
			stringDestroy(&string);
			return TEXT_ERROR;
		}
	}

	return TEXT_SUCCESS;	
}

int textResize(Text_t *text, unsigned int new_size) {
	char **new_data = (char **)realloc(text->data, new_size * sizeof(char *));
	if (!new_data)
		return TEXT_ERROR;

	text->data = new_data;
	text->capacity = new_size;
	return TEXT_SUCCESS;
}

int textSort(Text_t *text, int num) {
	if (!text)
		return TEXT_ERROR;

	qsort(text->data, &text->data[text->size - 1], num);
	
	return TEXT_SUCCESS;
}

int textWrite(Text_t *text, FILE *file) {
	if (!file || !text)
		return TEXT_ERROR;

	for (int i = 0; i < text->size; i++)
		fprintf(file, "%s\n", text->data[i]);

	return TEXT_SUCCESS;
}
