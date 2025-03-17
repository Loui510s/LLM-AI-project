#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

#define INPUT_SIZE 3
#define HIDDEN_SIZE 4
#define OUTPUT_SIZE 2
#define LEARNING_RATE 0.01

typedef struct {
    float weights_ih[HIDDEN_SIZE][INPUT_SIZE]; // ✅ This is correct
    float weights_ho[OUTPUT_SIZE][HIDDEN_SIZE];
    float hidden_bias[HIDDEN_SIZE];
    float output_bias[OUTPUT_SIZE];
} NeuralNetwork;

void initialize_model(NeuralNetwork *model);
void forward(NeuralNetwork *model, const float *input, float *hidden, float *output);
void train(NeuralNetwork *nn, float input[], float target[]);

void initialize_network(NeuralNetwork *nn);
void forward_pass(NeuralNetwork *nn, float input[], float output[]);

#endif // MODEL_H