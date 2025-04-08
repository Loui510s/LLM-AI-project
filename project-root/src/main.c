#include <stdio.h>
#include "model.h"
#include "matrix.h"

int main() {
    int input_size = 5;
    int hidden_size = 4;
    int output_size = 3;

    Model* model = create_model(input_size, hidden_size, output_size);

    Matrix* input = create_matrix(1, input_size);
    // Example input (manually fill for now)
    input->data[0] = 1;
    input->data[1] = 0;
    input->data[2] = 0;
    input->data[3] = 0;
    input->data[4] = 1;

    Matrix* output = model_forward(model, input);

    printf("Output:\n");
    for (int i = 0; i < output->rows * output->cols; i++) {
        printf("%f ", output->data[i]);
    }
    printf("\n");

    free_matrix(input);
    free_matrix(output);
    free_model(model);

    return 0;
}
