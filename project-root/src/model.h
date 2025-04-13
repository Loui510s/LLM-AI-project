#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

typedef struct {
    Matrix* W1;
    Matrix* b1;
    Matrix* W2;
    Matrix* b2;
    Matrix* hidden; // Add this
    Matrix* output; // Add this
    Matrix* dW1;
    Matrix* db1;
    Matrix* dW2;
    Matrix* db2;
} Model;

Model* create_model(int input_size, int hidden_size, int output_size);
void free_model(Model* model);
Matrix* model_forward(Model* model, Matrix* input);
void save_model(Model* model, const char* filename);
Model* load_model(const char* filename);

#endif

void model_backward(Model* model, Matrix* input, Matrix* target);
void model_update(Model* model, float learning_rate);
float calculate_loss(Matrix* predictions, Matrix* targets);
void softmax(float* input, float* output, int length);
float cross_entropy_loss(float* predicted, int label, int length);
