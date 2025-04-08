#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

typedef struct {
    Matrix* W1;
    Matrix* b1;
    Matrix* W2;
    Matrix* b2;
} Model;

Model* create_model(int input_size, int hidden_size, int output_size);
void free_model(Model* model);
Matrix* model_forward(Model* model, Matrix* input);

#endif
