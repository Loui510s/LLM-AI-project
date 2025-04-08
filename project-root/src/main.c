#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "matrix.h"
#include "model.h"

int main() {
    // 1. Tokenize input text
    const char* input_text = "hello";
    int token_count;
    int* tokens = tokenize(input_text, &token_count);

    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("%d ", tokens[i]);
    }
    printf("\n");

    // 2. Convert tokens into a 1xN input matrix
    Matrix* input_matrix = create_matrix(1, token_count);
    for (int i = 0; i < token_count; i++) {
        input_matrix->data[i] = (float)tokens[i];
    }

    // 3. Create model
    Model* model = create_model(token_count, 8, 4); // simple: 8 hidden

    // 4. Forward pass
    Matrix* output = model_forward(model, input_matrix); // Use model_forward
    printf("Output:\n");
    for (int i = 0; i < output->rows * output->cols; i++) {
        printf("%f ", output->data[i]);
    }
    printf("\n");

    // 5. Save model
    save_model(model, "model.bin");

    // 6. Load model
    Model* loaded = load_model("model.bin");

    printf("Loaded model forward pass:\n");
    Matrix* out2 = model_forward(loaded, input_matrix); // Use model_forward
    for (int i = 0; i < out2->rows * out2->cols; i++) {
        printf("%f ", out2->data[i]);
    }
    printf("\n");

    // Cleanup
    free_tokens(tokens);
    free_matrix(input_matrix);
    free_matrix(output);
    free_matrix(out2);
    free_model(model);
    free_model(loaded);

    return 0;
}
