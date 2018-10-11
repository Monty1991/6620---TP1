#ifndef __STRING_H__
#define __STRING_H__

typedef struct {
	char *data;
	unsigned int size;
	unsigned int capacity;
} String_t;

#define STRING_SUCCESS 0
#define STRING_ERROR 1

// Returns the contents of a string as a null terminated char array.
// NULL on error.
const char *stringC_str(String_t *string);

// Initializes a string.
// Returns STRING_SUCCESS on success
// STRING_ERROR on failure
int stringCreate(String_t *string);

// Cleanups a string.
void stringDestroy(String_t *string);

// Appends a char to the end of the string.
// Returns STRING_SUCCESS on success
// STRING_ERROR on failure
int stringPush_back(String_t *string, char c);

// Removes ownership of data from a string.
// The string needs to be initialized again.
char *stringStrip(String_t *string);

#endif /* __STRING_H__ */
