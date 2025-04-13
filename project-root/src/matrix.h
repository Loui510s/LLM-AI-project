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
void add_bias(Matrix* mat, Matrix* bias);
Matrix* mat_sigmoid(Matrix* mat);
Matrix* mat_sub(Matrix* a, Matrix* b);
Matrix* mat_transpose(Matrix* mat);
Matrix* mat_sum_rows(Matrix* mat);
Matrix* mat_elemwise_mul(Matrix* a, Matrix* b);
Matrix* mat_scale(Matrix* mat, float scalar);
void mat_sub_inplace(Matrix* a, Matrix* b);
void print_matrix(Matrix* mat);
Matrix* mat_apply(Matrix* mat, float (*func)(float));
Matrix* mat_sum_axis(Matrix* mat, int axis);
Matrix* mat_mul_transpose(Matrix* A, Matrix* B);
Matrix* mat_add(Matrix* A, Matrix* B);
#endif
