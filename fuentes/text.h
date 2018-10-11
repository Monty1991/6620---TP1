#ifndef __TEXT_H__
#define __TEXT_H__

// Represents a vector of string lines
typedef struct {
	char **data;
	unsigned int size;
	unsigned int capacity;
} Text_t;

#define TEXT_SUCCESS 0
#define TEXT_ERROR 1

#include <stdio.h>

// Initializes a text.
// Returns TEXT_SUCCESS on success
// TEXT_ERROR on failure.
int textCreate(Text_t *text);

// Cleanups a text.
void textDestroy(Text_t *text);

// Reads from a file
// Returns TEXT_SUCCESS on success
// TEXT_ERROR on failure.
int textRead(Text_t *text, FILE *file);

// sorts the lines
// if num == 0 -> sorts lexicographicaly
// else numerical (interprets the lines as numbers)
// Returns TEXT_SUCCESS on success
// TEXT_ERROR on failure.
int textSort(Text_t *text, int num);

// Writes to a file
// Returns TEXT_SUCCESS on success
// TEXT_ERROR on failure.
int textWrite(Text_t *text, FILE *file);

#endif /* __TEXT_H__ */
