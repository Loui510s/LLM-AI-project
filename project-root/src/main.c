#include <stdio.h>
#include <stdlib.h>
#include "model.h"

int main() {
    NeuralNetwork nn;
    initialize_network(&nn);

    // Example training data: XOR problem
    float input1[] = {0, 0, 1};
    float input2[] = {0, 1, 1};
    float target1[] = {0, 1};
    float target2[] = {1, 0};

    for (int i = 0; i < 1000; i++) {
        train(&nn, input1, target1);
        train(&nn, input2, target2);
    }

    float output[OUTPUT_SIZE];
    forward_pass(&nn, input1, output);
    printf("Output for [0,0,1]: %.3f, %.3f\n", output[0], output[1]);

    forward_pass(&nn, input2, output);
    printf("Output for [0,1,1]: %.3f, %.3f\n", output[0], output[1]);

    return 0;
}
