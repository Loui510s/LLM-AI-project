#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "matrix.h"

void initialize_model(Model *model) {
    initialize_matrix(model->weights_ih, INPUT_SIZE, HIDDEN_SIZE);
    initialize_matrix(model->weights_ho, HIDDEN_SIZE, OUTPUT_SIZE);
}

void forward(Model *model, const float *input, float *hidden, float *output) {
    multiply_matrices(input, model->weights_ih, hidden);
    multiply_matrices(hidden, model->weights_ho, output);
}
