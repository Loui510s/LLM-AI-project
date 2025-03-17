#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"

// Helper function to generate random numbers
float rand_float() {
    return (float)rand() / RAND_MAX * 2.0 - 1.0; // Random value between -1 and 1
}

void initialize_network(NeuralNetwork *nn) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            nn->weights_ih[i][j] = rand_float();
        }
        nn->hidden_bias[i] = rand_float();
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            nn->weights_ho[i][j] = rand_float();
        }
        nn->output_bias[i] = rand_float();
    }
}

void forward_pass(NeuralNetwork *nn, float input[], float output[]) {
    float hidden[HIDDEN_SIZE];

    // Compute Hidden Layer Activations
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        hidden[i] = nn->hidden_bias[i];
        for (int j = 0; j < INPUT_SIZE; j++) {
            hidden[i] += nn->weights_ih[i][j] * input[j];
        }
        // Apply Activation Function (ReLU)
        hidden[i] = fmaxf(0, hidden[i]);  
    }

    // Compute Output Layer Activations
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        output[i] = nn->output_bias[i];
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            output[i] += nn->weights_ho[i][j] * hidden[j];
        }
        // Apply Activation Function (Sigmoid for probability outputs)
        output[i] = 1.0f / (1.0f + expf(-output[i]));
    }
}

void train(NeuralNetwork *nn, float input[], float target[]) {
    float output[OUTPUT_SIZE];
    forward_pass(nn, input, output);

    float output_error[OUTPUT_SIZE];
    float hidden_error[HIDDEN_SIZE];

    // Compute output layer error
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        output_error[i] = (target[i] - output[i]) * output[i] * (1 - output[i]); // Derivative of Sigmoid
    }

    // Compute hidden layer error
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        hidden_error[i] = 0;
        for (int j = 0; j < OUTPUT_SIZE; j++) {
            hidden_error[i] += output_error[j] * nn->weights_ho[j][i];
        }
        hidden_error[i] *= (hidden_error[i] > 0) ? 1 : 0; // Derivative of ReLU
    }

    // Update Weights (Gradient Descent)
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            nn->weights_ho[i][j] += LEARNING_RATE * output_error[i] * j;
        }
        nn->output_bias[i] += LEARNING_RATE * output_error[i];
    }

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            nn->weights_ih[i][j] += LEARNING_RATE * hidden_error[i] * j;
        }
        nn->hidden_bias[i] += LEARNING_RATE * hidden_error[i];
    }
}
