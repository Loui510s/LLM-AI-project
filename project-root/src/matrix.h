#ifndef MATRIX_H
#define MATRIX_H

void initialize_matrix(float *matrix, int rows, int cols);
void multiply_matrices(const float *matrix1, const float *matrix2, float *result);
void add_matrices(float *A, float *B, float *C, int rows, int cols);

typedef struct {
    // Define the contents of the Matrix structure
    int rows;
    int cols;
    float* data;
} Matrix;

#endif // MATRIX_H
