#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

#define INPUT_SIZE 10
#define HIDDEN_SIZE 20
#define OUTPUT_SIZE 5

typedef struct {
    float weights_ih[INPUT_SIZE * HIDDEN_SIZE];
    float weights_ho[HIDDEN_SIZE * OUTPUT_SIZE];
} NeuralNetwork;

void initialize_model(NeuralNetwork *model);
void forward(NeuralNetwork *model, const float *input, float *hidden, float *output);

#endif // MODEL_H