#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "matrix.h"

void initialize_model(NeuralNetwork *model) {
    initialize_matrix((float *)model->weights_ih, INPUT_SIZE, HIDDEN_SIZE);
    initialize_matrix((float *)model->weights_ho, HIDDEN_SIZE, OUTPUT_SIZE);
}

void forward(NeuralNetwork *model, float *input, float *output) {
    float hidden[HIDDEN_SIZE];
    multiply_matrices(input, (float *)model->weights_ih, hidden, 1, INPUT_SIZE, HIDDEN_SIZE);
    multiply_matrices(hidden, (float *)model->weights_ho, output, 1, HIDDEN_SIZE, OUTPUT_SIZE);
}
