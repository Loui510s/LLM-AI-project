#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix* create_matrix(int rows, int cols) {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (float*)calloc(rows * cols, sizeof(float));
    return m;
}

void free_matrix(Matrix* m) {
    free(m->data);
    free(m);
}

Matrix* mat_mul(Matrix* a, Matrix* b) {
    if (a->cols != b->rows) return NULL;
    Matrix* result = create_matrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            float sum = 0.0;
            for (int k = 0; k < a->cols; k++) {
                sum += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
            result->data[i * b->cols + j] = sum;
        }
    }
    return result;
}

Matrix* mat_relu(Matrix* m) {
    Matrix* result = create_matrix(m->rows, m->cols);
    for (int i = 0; i < m->rows * m->cols; i++) {
        result->data[i] = fmaxf(0, m->data[i]);
    }
    return result;
}

Matrix* mat_softmax(Matrix* m) {
    Matrix* result = create_matrix(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        float sum = 0.0;
        for (int j = 0; j < m->cols; j++) {
            result->data[i * m->cols + j] = expf(m->data[i * m->cols + j]);
            sum += result->data[i * m->cols + j];
        }
        for (int j = 0; j < m->cols; j++) {
            result->data[i * m->cols + j] /= sum;
        }
    }
    return result;
}
