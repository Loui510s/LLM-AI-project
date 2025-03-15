Matrix multiply_matrices(Matrix *A, Matrix *B) {
    if (A->cols != B->rows) {
        fprintf(stderr, "Error: Matrix dimensions do not match\n");
        exit(1);
    }

    Matrix result;
    result.rows = A->rows;
    result.cols = B->cols;
    result.data = malloc(result.rows * result.cols * sizeof(float));

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.data[i * result.cols + j] = 0;
            for (int k = 0; k < A->cols; k++) {
                result.data[i * result.cols + j] += A->data[i * A->cols + k] * B->data[k * B->cols + j];
            }
        }

    }
    return result;
}

