#ifndef _PROBLEMS_H_
#define _PROBLEMS_H_

#include <stdlib.h>
#include <limits.h>
#include "../practica2/cdlist.h"

typedef long long unsigned Natural;

/* Fibonacci numbers */

/*
	** Recursive algorithm for calculating fibonacci numbers
	** Time complexity: O(2^n)
	** Space complexity: O(n)
*/
Natural fib_recursive(unsigned n);

/*
	** Memoized recursive algorithm for fibonacci numbers
	** This implementation assumes that memo has enough capacity
	** to store n integers and that they are initialized to
	** Time complexity: O(n)
	** Space complexity: O(n)
*/
Natural fib_memo(unsigned n, Natural memo[]);

/*
	** Iterative algorithm for fibonacci numbers
	** Time complexity: O(n)
	** Space complexity: O(1)
*/
Natural fib_iterative(unsigned n);

/* Survivor simulation */

/*
	** Survivor simulation with circular linked lists
	** Time complexity: O(n)
	** Space complexity: O(n)
*/    
unsigned survivor_clist(unsigned n);

/*
	** Survivor simulation with a recursive algorithm 
	** Time complexity: O(log n)
	** Space complexity: O(log n)
*/    
unsigned survivor_recursive(unsigned n);

/*
	** Survivor simulation using ... 
	** Time complexity: O(1)
	** Space complexity: O(1)
*/    
unsigned survivor_constant(unsigned n);

/* Find peak */
/* 
Given an array, a peak is an element such that is greater or equal to
both of its neighnours. If the element is itself on the start or the
end of the array, then it must be greater or equal to its only neighbour
*/

/*
	** Find a peak comparing all elements, or until one is found
	** Time complexity: O(n)
	** Space complexity: O(1)
*/
size_t find_peak_linear(int array[], size_t len);

/*
	** Find a peak dividing the array in halves
	** Time complexity: O(log n)
	** Space complexity: O(1)
*/
size_t find_peak_log(int array[], size_t len);


/* Find Minimum Path */
/*
Given a m x n matrix, find the minimum sum of matrix entries
from top left to bottom right, moving in any combination of
right and down moves
For example, for the following matrix we have:
[ 1, 3]
[ 5, 4]
and the minimum path 8, since there are only two possible ways
to get from corner to corner:
Down, Right: Path sum is 1 + 5 + 4 = 10
Right, Down: Path sum is 1 + 3 + 4 = 8
Then the minimum path is 8
*/

/*
	** Recursively compute the minimum path for submatrices
	** Time complexity: O(C(m + n - 2, n - 1))
	** Space complexity: O(m + n)
*/
int find_min_path_recursive(int **matrix, size_t i, size_t j);

/*
	** Recursively compute while memoizing the minimum path for submatrices
	** Argument preconditions: memo must be of type int[m][n] filled with -1
	** Time complexity: O(m * n)
	** Space complexity: O(m * n)
*/
int find_min_path_memo(int **matrix, size_t i, size_t j, int **memo);

/*
	** Time complexity: O(m * n)
	** Space complexity: O(m)
*/
int find_min_path_iterative(int **matrix, size_t i, size_t j);

/* Find sum in array */
/* 
Given an array of integers, determines
if there exists a subset of the array that
sum to n
*/

/*
	** Recursive algorithm for finding sum
	** Time complexity: O(2^n)
	** Space complexity: O(1)
*/
int find_sum(int n, int array[], size_t len);

/* Compute power */
/*
	** Time complexity: O(log n)
	** Space complexity: O(log n)
*/
double power(double base, unsigned n);

/* Evaluate polynomial */
/*
	** Time complexity: O(n)
	** Space complexity: O(1)
*/
double peval(double c[], int n, double x);


#endif // _PROBLEMS_H_