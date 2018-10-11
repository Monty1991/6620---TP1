#ifndef __GETLINE_H__
#define __GETLINE_H__

#include "string.h"

#include <stdio.h>

#define GETLINE_SUCCESS 0
#define GETLINE_ERROR 1

// Initializes a string containing the next line from file_in
// the new line character is not included.
// Returns GETLINE_SUCCESS on success, GETLINE_ERROR on error.
int getline(String_t *str, FILE *file_in);

#endif /* __GETLINE_H__ */
