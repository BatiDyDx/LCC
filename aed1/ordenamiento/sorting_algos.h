#ifndef __SORT_ALGOS_H__
#define __SORT_ALGOS_H__ // Sorting algorithms implementations

/*
 * Performs binary search algorithm on a sorted array of integers, returns the
 * index of v if it is in a, -1 otherwise
*/
int binsearch(int a[], unsigned const len, int v);

/*
 * Bubble sort sorting algorithm
*/
void bubbleSort(int a[], unsigned const len);

void insertionSort(int a[], unsigned const len);

/*
 * Perform insertion sort using less swaps to improve runtime
*/
void insertionSort_noswap(int a[], unsigned const len);

/*
 * Selection Sort algorithm
*/
void selectionSort(int a[], unsigned const len);

/*
 * Merge function for the merge sort algorithm
*/
void merge(int a1[], int a2[], unsigned const len1, unsigned const len2);

/*
 * Merge sort algorithm
*/
int* mergeSort(int a[], unsigned const len);

/*
 * Quick sort algorithm
*/
void quickSort(int a[], unsigned const len);

/*
 * Lomuto's partition algorithm for quick sort. Creates two partitions in the
 * array such that:
 * [   <= p  |  > p  ]
 * Returns the length of the first partition (number of elements less than or
 * equal to p in arr).
*/
unsigned lomutos_partition(int a[], unsigned const len, int p);

/*
 * Quick sort algorithm adapted to use the lomutos double partition algorithm
*/
void quickSort_ldp();

/*
 * Lomuto's partition algorithm variant, partitions the array
 * into three segments:
 * [  < p  |   == p   |  > p  ]
 * This way, sorting arrays with many repeated elements becomes faster.
 * Stores in the buffers j,k the length of the two first partitions respectively
*/
void lomutos_double_partition();

int median();

/**/
void sort_with_missing_natural(int a[], unsigned const n);

void mergeSort_adaptive();

#endif /* __SORT_ALGOS_H__ */