typedef struct {
    int rows;
    int cols;
    float *data;
} Matrix;

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

float mean_squared_error(Matrix *output, Matrix *target) {
    float loss = 0;
    for (int i = 0; i < output->rows * output->cols; i++) {
        loss += (output->data[i] - target->data[i]) * (output->data[i] - target->data[i]);
    }
    return loss / (output->rows * output->cols);
}



void relu(matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        if (m->data[i] < 0) {
            m->data[i] = 0;
        }
    }
}
