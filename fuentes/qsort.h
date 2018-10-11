#ifndef __QSORT_H__
#define __QSORT_H__

// Orders an array of null terminated strings
// if num is 0, the order is lexicographical
// if num is other than zero, the order is numerical (asumes they are numbers)
void qsort(char **izq, char **der, int num);

#endif /* __QSORT_H__ */
