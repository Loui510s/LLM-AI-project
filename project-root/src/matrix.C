#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void multiply_matrices(float *A, float *B, float *C, int A_rows, int A_cols, int B_cols) {
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            C[i * B_cols + j] = 0;
            for (int k = 0; k < A_cols; k++) {
                C[i * B_cols + j] += A[i * A_cols + k] * B[k * B_cols + j];
            }
        }
    }
}

void add_matrices(float *A, float *B, float *C, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        C[i] = A[i] + B[i];
    }
}

void initialize_matrix(float *matrix, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = (float)rand() / RAND_MAX;
    }
}
