#include "sorting_algos.h"
#include <string.h>

static inline void swap(int *x, int *y) {
	// Swap x and y values using XOR
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

int binsearch(int a[], unsigned const len, int v) {
	if (len == 0)
		return -1;

  unsigned low = 0, high = len;
	unsigned mid;
	while (low <= high) {
		mid = (high + low) / 2;
		if (v == a[mid])
			return mid;
		else if (v < a[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

void bubbleSort(int a[], unsigned const len) {
	int stop = 0;
	while (!stop) {
		stop = 1;
    for (int i = 0; i < len - 1; j++) {
      // If some change is made, then the array may not be sorted
      if (a[j] > a[j + 1]) {
        swap(a + j, a + j + 1);
        stop = 0;
      }
    }
	}
}

void insertionSort(int a[], unsigned const len) {
  for (int i = 1; i < len; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      if (a[j] > a[j + 1])
        swap(a + j, a + j + 1);
      else
        break;
    }
  }
}

void insertionSort_noswap(int a[], unsigned const len) {
  for (int i = 1; i < len; ++i) {
    int j;
    for (j = i - 1; j >= 0; --j) {
      if (a[j] <= a[i]) {
        int tmp = a[i];
        // Shift one position to the right each element from position j + 1 to
        // to position i. Number of elements to move is i - j - 1, since there
        // are i - j elements from j + 1 to i, and a[i] doesnt shift to the
        // right (it moves to the front)
        memmove(a + j + 1, a + j + 2, sizeof(int) * (i - j - 1));
        a[j + 1] = tmp;
        break;
      } 
      // Case where a[i] is the minimum so far
      // Insert it first on the array
      else if (j == 0) {
        int tmp = a[i];
        memmove(a, a + 1, sizeof(int) * i);
        a[0] = tmp;
      }
    }
  }
}

void selectionSort(int a[], unsigned const len) {
  for (unsigned i = 0; i < len - 1; ++i) {
    unsigned min_index = i;
    for (unsigned j = i + 1; j < len; ++j)
      if (a[min_index] > a[j])
        min_index = j;
    if (min_index == i)
      continue;
    swap(a + i, a + min_index);
  }
}

int* merge(int a1[], int a2[], unsigned const len1, unsigned const len2) {
  int i = 0, j = 0;
  while (i < len1 && j < len2) {
    if (a1[])
  }
}


static void mergeSort_impl(int a[], int buf[], unsigned const len) {
  if (len <= 1)
    return a;
  unsigned mid = len / 2;
  // If len = 2k, then len(b1) = len(b2) = k
  // If len is 2k + 1, then len(b1) = k and len(b2) = k + 1
  int *b1 = mergeSort(a, mid);
  int *b2 = mergeSort(a + mid, len - mid);
  return merge(b1, b2, mid, len - mid);
}

void quickSort(int a[], unsigned const len) {
  if (len <= 1)
    return a;
  int p = a[0];
  
}

unsigned lomutos_partition(int a[], unsigned const len, int p) {
  int j = 1;
  for (int i = 1; i < len; ++i)
    if (a[i] <= p) {
      if (i != j)
        swap(a + i, a + j);
      j++;
    }
  return j;
}


void sort_with_missing_natural(int a[], unsigned const n) {
  unsigned array_sum = 0, naturals_sum;
  // Sum of naturals from 1 to n + 1
  naturals_sum = ((n + 1) * (n + 2)) / 2;
  // Sum of array
  for (unsigned i = 0; i < n; array_sum += a[i++]);
  /*
  Suppose k is the natural between 1 and n + 1 missing from a.
  Then naturals_sum = 1 + 2 + ... + k + ... + n and
  array_sum = 1 + 2 + ... + k - 1 + k + 1 + ... + n
  So it must be k = naturals_sum - array_sum
  */
  unsigned missing_natural = naturals_sum - array_sum;
  // Then sorting a will be equivalent to having the array
  // [1, 2, ..., k - 1, k + 1, ..., n]
  for (unsigned i = 0; i < n; i++)
    a[i] = (i + 1) < missing_natural ? (i + 1) : (i + 2);
}
