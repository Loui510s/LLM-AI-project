#ifndef MODEL_H
#define MODEL_H

#define INPUT_SIZE 10
#define HIDDEN_SIZE 5
#define OUTPUT_SIZE 10

typedef struct {
    float weights_ih[INPUT_SIZE][HIDDEN_SIZE];
    float weights_ho[HIDDEN_SIZE][OUTPUT_SIZE];
} NeuralNetwork;

void initialize_model(NeuralNetwork *model);
void forward(NeuralNetwork *model, float *input, float *output);

#endif // MODEL_H
