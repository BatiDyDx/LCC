#include "matrix.h"

struct matrix_impl {
    unsigned nrows, ncols;
    double **values;
};

unsigned row_numbers(Matrix* m) {
    return m->nrows;
}

unsigned col_numbers(Matrix* m) {
    return m->ncols;
}

Matrix* create_matrix(Index nrows, Index ncols) {
    Matrix *m = malloc(sizeof(Matrix));
    assert(m != NULL);
    m->nrows = nrows;
    m->ncols = ncols;
    m->values = malloc(sizeof(double*) * nrows);
    assert(m->values != NULL);
    for (int i = 0; i < nrows; i++) {
        m->values[i] = malloc(sizeof(double) * ncols);
        assert(m->values[i] != NULL);
        for (int j = 0; j < ncols; j++)
            m->values[i][j] = 0.0;
    }
    return m;
}

void destroy_matrix(Matrix *m) {
    for (int i = 0; i < m->nrows; i++)
        free(m->values[i]);
    free(m->values);
    free(m);
}

double read_matrix(Matrix *m, Index row, Index col) {
    assert(row < m->nrows);
    assert(col < m->ncols);

    return m->values[row][col];
}

void write_matrix(Matrix *m, Index row, Index col, const double data) {
    assert(row < m->nrows);
    assert(col < m->ncols);
    m->values[row][col] = data;
}

void change_rows(Matrix *m, Index i, Index j) {
    assert(i < m->nrows && j < m->nrows);
    double* tmp = m->values[i];
    m->values[i] = m->values[j];
    m->values[j] = tmp;
}

void insert_row(Matrix *m, double *new_row, Index row_num) {
    assert(row_num <= m->nrows);
    m->values = realloc(m->values, sizeof(double*) * (++m->nrows));
    assert(m->values != NULL);
    for (int i = m->nrows - 1; i > row_num; i--)
        m->values[i] = m->values[i - 1];
    double* row_cpy = malloc(sizeof(double) * m->ncols);
    assert(row_cpy != NULL);
    memcpy(row_cpy, new_row, sizeof(double) * m->ncols);
    m->values[row_num] = row_cpy;
}

void print_matrix(Matrix* m) {
    for (size_t i = 0; i < m->nrows; i++) {
        printf("[ ");
        for (size_t j = 0; j < m->ncols; j++)
            printf("%lf ", m->values[i][j]);
        printf("]\n");
    }
}
