#include <stdio.h>   // For printf
#include <stdlib.h>  // For malloc, calloc, free
#include <math.h>    // For fmaxf, expf
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

void print_matrix(Matrix* mat) {
    const char* class_labels[] = {"Class 0", "Class 1"}; // Update class labels as needed
    for (int i = 0; i < mat->rows; i++) {
        int predicted_class = 0;
        float max_prob = mat->data[i * mat->cols];
        for (int j = 1; j < mat->cols; j++) {
            if (mat->data[i * mat->cols + j] > max_prob) {
                max_prob = mat->data[i * mat->cols + j];
                predicted_class = j;
            }
        }
        for (int j = 0; j < mat->cols; j++) {
            printf("%f \n", mat->data[i * mat->cols + j]);
        }
        printf("Predicted class: %s\n", class_labels[predicted_class]);
    }
}
Matrix* mat_apply(Matrix* mat, float (*func)(float)) {
    Matrix* result = create_matrix(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows * mat->cols; i++) {
        result->data[i] = func(mat->data[i]);
    }
    return result;
}
void add_bias(Matrix *mat, Matrix *bias)
{
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->data[i * mat->cols + j] += bias->data[j];
        }
    }
}

Matrix* mat_sigmoid(Matrix* mat) {
    Matrix* result = create_matrix(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows * mat->cols; i++) {
        result->data[i] = 1.0f / (1.0f + expf(-mat->data[i]));
    }
    return result;
}

Matrix* mat_sub(Matrix* a, Matrix* b) {
    Matrix* result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows * a->cols; i++) {
        result->data[i] = a->data[i] - b->data[i];
    }
    return result;
}

Matrix* mat_transpose(Matrix* mat) {
    Matrix* result = create_matrix(mat->cols, mat->rows);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            result->data[j * mat->rows + i] = mat->data[i * mat->cols + j];
        }
    }
    return result;
}

Matrix* mat_sum_rows(Matrix* mat) {
    Matrix* result = create_matrix(1, mat->cols);
    for (int j = 0; j < mat->cols; j++) {
        float sum = 0.0f;
        for (int i = 0; i < mat->rows; i++) {
            sum += mat->data[i * mat->cols + j];
        }
        result->data[j] = sum;
    }
    return result;
}


Matrix* mat_elemwise_mul(Matrix* a, Matrix* b) {
    Matrix* result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows * a->cols; i++) {
        result->data[i] = a->data[i] * b->data[i];
    }
    return result;
}

Matrix* mat_scale(Matrix* mat, float scalar) {
    Matrix* result = create_matrix(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows * mat->cols; i++) {
        result->data[i] = mat->data[i] * scalar;
    }
    return result;
}

void mat_sub_inplace(Matrix* a, Matrix* b) {
    for (int i = 0; i < a->rows * a->cols; i++) {
        a->data[i] -= b->data[i];
    }
}
Matrix* mat_add(Matrix* A, Matrix* B) {
    Matrix* result = create_matrix(A->rows, A->cols);
    for (int i = 0; i < A->rows * A->cols; i++) {
        result->data[i] = A->data[i] + B->data[i];
    }
    return result;
}
Matrix* mat_mul_transpose(Matrix* A, Matrix* B) {
    Matrix* result = create_matrix(A->rows, B->rows);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->rows; j++) {
            float sum = 0.0f;
            for (int k = 0; k < A->cols; k++) {
                sum += A->data[i * A->cols + k] * B->data[j * B->cols + k];
            }
            result->data[i * B->rows + j] = sum;
        }
    }
    return result;
}
Matrix* mat_sum_axis(Matrix* mat, int axis) {
    if (axis == 0) { // Sum along rows
        Matrix* result = create_matrix(1, mat->cols);
        for (int j = 0; j < mat->cols; j++) {
            float sum = 0.0f;
            for (int i = 0; i < mat->rows; i++) {
                sum += mat->data[i * mat->cols + j];
            }
            result->data[j] = sum;
        }
        return result;
    } else { // Sum along columns
        Matrix* result = create_matrix(mat->rows, 1);
        for (int i = 0; i < mat->rows; i++) {
            float sum = 0.0f;
            for (int j = 0; j < mat->cols; j++) {
                sum += mat->data[i * mat->cols + j];
            }
            result->data[i] = sum;
        }
        return result;
    }
}