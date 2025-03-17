#ifndef MATRIX_H
#define MATRIX_H

void multiply_matrices(const float *A, float *B, float *C, int A_rows, int A_cols, int B_cols);
void add_matrices(float *A, float *B, float *C, int rows, int cols);
void initialize_matrix(float *matrix, int rows, int cols);

#endif // MATRIX_H