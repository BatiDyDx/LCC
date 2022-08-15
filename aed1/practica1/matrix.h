#ifndef MATRIX_H
    
    #include <assert.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #define MATRIX_H
    
    typedef const unsigned Index;

    typedef struct matrix_impl Matrix;

    // Creates a Matrix struct with the given dimensions
    Matrix* create_matrix(unsigned nrows, unsigned ncols);

    // Returns the number of rows
    unsigned row_numbers(Matrix* m);

    // Returns the number of columns
    unsigned col_numbers(Matrix* m);

    // Frees a Matrix
    void destroy_matrix(Matrix *m);

    // Returns the value in the given position of the matrix
    double read_matrix(Matrix *m, unsigned row, unsigned col);

    // Writes the value given to the matrix in the position specified
    void write_matrix(Matrix *m, unsigned row, unsigned col, double data);

    // Moves the ith-row to the jth-row and vice-versa
    void change_rows(Matrix *m, unsigned i, unsigned j);

    // Inserts a new row to the matrix
    void insert_row(Matrix *m, double *new_row, unsigned row_num);

    // Prints all the matrix entries
    void print_matrix(Matrix *m);

#endif