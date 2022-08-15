#ifndef __UTILS_H__
#define __UTILS_H__

// Returns a physical copy of data
typedef void *(*CopyFunction)(void *data);

// Returns a negative if data1 < data2, 0 if equal, 1 otherwise
typedef int (*CompareFunction)(void *data1, void *data2);

// Frees the memory allocated for data
typedef void (*DestroyFunction)(void *data);

// Displays information of data
typedef void (*VisitFunction)(void *data);

// Like VisitFunction, except it takes an additional argument
typedef void (*ExtraVisitFunction)(void *data, void *extra);

// Returns 0 if data does not match the predicate, some
// non-zero integer if it does
typedef int (*Predicate)(void *data);

// Returns an unsigned int for data
typedef unsigned (*HashFunction)(void *data);

/**
 * Hash function for strings proposed by Kernighan & Ritchie in "The C
 * Programming Language (Second Ed.)".
 */
unsigned KRHash(char *s);

#endif /* __UTILS_H__ */

