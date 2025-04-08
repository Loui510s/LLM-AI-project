#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    float* data;
} Matrix;

Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix* m);
Matrix* mat_mul(Matrix* a, Matrix* b);
Matrix* mat_relu(Matrix* m);
Matrix* mat_softmax(Matrix* m);

#endif
