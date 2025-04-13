#include <stdlib.h>
#include <math.h>
#include "model.h"
#include "matrix.h"

// Wrapper for tanh to work with float
float tanh_float(float x) {
    return (float)tanh((double)x);
}

Matrix* model_forward(Model* model, Matrix* input) {
    Matrix* hidden = mat_add(mat_mul(input, model->W1), model->b1); // Hidden layer
    mat_apply(hidden, tanh_float); // Apply activation function (e.g., tanh)

    Matrix* output = mat_add(mat_mul(hidden, model->W2), model->b2); // Output layer
    free_matrix(hidden);
    return output;
}

void initialize_weights(Matrix* matrix) {
    for (int i = 0; i < matrix->rows * matrix->cols; i++) {
        matrix->data[i] = ((float)rand() / RAND_MAX) * 0.01f; // Small random values
    }
}

Model* create_model(int input_size, int hidden_size, int output_size) {
    Model* model = (Model*)malloc(sizeof(Model));
    model->W1 = create_matrix(input_size, hidden_size);
    model->b1 = create_matrix(1, hidden_size);
    model->W2 = create_matrix(hidden_size, output_size);
    model->b2 = create_matrix(1, output_size);

    initialize_weights(model->W1);
    initialize_weights(model->b1);
    initialize_weights(model->W2);
    initialize_weights(model->b2);

    return model;
}

void free_model(Model* model) {
    free_matrix(model->W1);
    free_matrix(model->b1);
    free_matrix(model->W2);
    free_matrix(model->b2);
    free(model);
}

void softmax(float* input, float* output, int length) {
    float max = input[0];
    for (int i = 1; i < length; i++) {
        if (input[i] > max) max = input[i]; // Find the maximum value for numerical stability
    }

    float sum = 0.0f;
    for (int i = 0; i < length; i++) {
        output[i] = expf(input[i] - max); // Subtract max for numerical stability
        sum += output[i];
    }

    for (int i = 0; i < length; i++) {
        output[i] /= sum; // Normalize to make the sum equal to 1
    }
}

float cross_entropy_loss(float* predicted, int label, int length) {
    float epsilon = 1e-10f; // Small value to prevent log(0)
    return -logf(predicted[label] + epsilon); // Negative log of the probability of the correct class
}


void model_backward(Model* model, Matrix* input, Matrix* target) {
    model->dW2 = mat_mul_transpose(model->hidden, mat_sub(model->output, target));
    model->db2 = mat_sum_axis(mat_sub(model->output, target), 0);

    Matrix* hidden_error = mat_mul_transpose(model->output, model->W2);
    model->dW1 = mat_mul_transpose(input, hidden_error);
    model->db1 = mat_sum_axis(hidden_error, 0);

    free_matrix(hidden_error);
}

void model_update(Model* model, float lr) {
    mat_sub_inplace(model->W1, mat_scale(model->dW1, lr));
    mat_sub_inplace(model->b1, mat_scale(model->db1, lr));
    mat_sub_inplace(model->W2, mat_scale(model->dW2, lr));
    mat_sub_inplace(model->b2, mat_scale(model->db2, lr));

    // Free gradients
    free_matrix(model->dW1);
    free_matrix(model->db1);
    free_matrix(model->dW2);
    free_matrix(model->db2);
}