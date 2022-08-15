#include "matrix.h"

struct matrix_impl {
    size_t nrows, ncols;
    double *values;
};

unsigned row_numbers(Matrix* m) {
    return m->nrows;
}

unsigned col_numbers(Matrix* m) {
    return m->ncols;
}

Matrix* create_matrix(Index nrows, Index ncols) {
    Matrix* m = (Matrix*) malloc(sizeof(Matrix));
    assert(m != NULL);
    m->nrows = nrows;
    m->ncols = ncols;
    m->values = malloc(sizeof(double) * nrows * ncols);
    assert(m->values != NULL);
    for (int i = 0; i < nrows * ncols; i++)
        m->values[i] = 0.0;
    return m;
}

void destroy_matrix(Matrix *m) {
    free(m->values);
    free(m);
}

double read_matrix(Matrix *m, Index row, Index col) {
    assert(row < m->nrows);
    assert(col < m->ncols);

    return m->values[row * m->ncols + col];
}

void write_matrix(Matrix *m, Index row, Index col, const double data) {
    assert(row < m->nrows);
    assert(col < m->ncols);

    m->values[row * m->ncols + col] = data;
}

void change_rows(Matrix *m, Index i, Index j) {
    assert(i < m->nrows && j < m->nrows);
    size_t bytes = sizeof(double) * m->ncols;
    double *tmp = malloc(bytes);
    assert(tmp != NULL);
    memcpy(tmp, m->values + (i * m->ncols), bytes);
    memcpy(m->values + (i * m->ncols), m->values + (j * m->ncols), bytes);
    memcpy(m->values + (j * m->ncols), tmp, bytes);
    free(tmp);
}

void insert_row(Matrix *m, double *new_row, Index row_num) {
    assert(row_num <= m->nrows);
    m->values = realloc(m->values, sizeof(double) * (++m->nrows) * (m->ncols));
    assert(m->values != NULL);
    for (int k = (m->nrows * m->ncols) - 1; k >= row_num * m->ncols; k--)
        m->values[k + m->ncols] = m->values[k];
    for (int k = 0; k < m->ncols; k++)
        m->values[row_num * m->ncols + k] = new_row[k];
}

void print_matrix(Matrix* m) {
    for (size_t i = 0; i < m->nrows; i++) {
        printf("[ ");
        for (size_t j = 0; j < m->ncols; j++)
            printf("%lf ", m->values[i * m->ncols + j]);
        printf("]\n");
    }
}