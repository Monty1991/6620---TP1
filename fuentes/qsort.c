#include "qsort.h"

#include <stdio.h>

typedef int (* compartor_t)(const char *izq, const char *der);

// returns -1 if x < y
// 0 if x == y
// 1 if x > y
int compare_char(const char *x, const char *y);

// returns -1 if x < y
// 0 if x == y
// 1 if x > y
int compare_num(const char *x, const char *y);

// returns the number that represents str
// stops at the first non digit char
int my_atoi(const char *str);

// partitions an array of strings.
// returns the pivot
char **partition(char **izq, char **der, compartor_t comparator);

// qsort for lexicographical order
void qsort_lexicographical(char **izq, char **der);

// qsort for numerical order
void qsort_numerical(char **izq, char **der);

// swaps 2 pointers to string inplace
void swap(char **izq, char **der);

int compare_char(const char *x, const char *y) {
	while(*x == *y) {
		if (*x == '\0')
			return 0;
		x++;
		y++;
	}

	if (*x < *y)
		return -1;

	return 1;
}

int compare_num(const char *x, const char *y) {
	int _x = my_atoi(x), _y = my_atoi(y);
	if (_x < _y)
		return -1;

	if (_x > _y)
		return 1;

	return 0;
}

int my_atoi(const char *str) {
	int num = 0;
	char digit = '0';
	do {
		num *= 10;
		num += digit - '0';
		digit = *str++;
	} while((digit >= '0') &&(digit <= '9'));

	return num;
}

char **partition(char **izq, char **der, compartor_t comparator) {
	char *pivot = *izq;
	char **begin = izq - 1;
	char **end = der + 1;
	while (1) {
		do {
			begin++;
		} while(comparator(*begin, pivot) < 0);

		do {
			end--;
		} while(comparator(*end, pivot) > 0);

		if (begin >= end)
			return end;

		swap(begin, end);
	}
}

void qsort_lexicographical(char **izq, char **der) {
	if (der <= izq)
		return;

	char **pivot = partition(izq, der, compare_char);
	qsort_lexicographical(izq, pivot);
	qsort_lexicographical(pivot + 1, der);
}

void qsort_numerical(char **izq, char **der) {
	if (der <= izq)
		return;

	char **pivot = partition(izq, der, compare_num);
	qsort_numerical(izq, pivot);
	qsort_numerical(pivot + 1, der);
}

void qsort(char **izq, char **der, int num) {
	if (!num)
		qsort_lexicographical(izq, der);
	else
		qsort_numerical(izq, der);
}

void swap(char **izq, char **der) {
	char *temp = *izq;
	*izq = *der;
	*der = temp;
}
