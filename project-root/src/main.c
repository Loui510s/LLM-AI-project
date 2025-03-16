#include <stdio.h>
#include "tokenizer.h"
#include "model.h"

int main() {
    char text[] = "Hello world this is a basic tokenizer example";
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int token_count = 0;
    char vocab[VOCAB_SIZE][MAX_TOKEN_LENGTH];
    int vocab_size = 0;

    // Preprocess and tokenize text
    preprocess_text(text);
    tokenize(text, tokens, &token_count);

    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        int token_id = get_token_id(tokens[i], vocab, vocab_size);
        if (token_id == -1) {
            token_id = add_token_to_vocab(tokens[i], vocab, &vocab_size);
        }
        printf("Token: %s, ID: %d\n", tokens[i], token_id);
    }

    // Create and test a neural network
    NeuralNetwork model;
    initialize_model(&model);

    float input[INPUT_SIZE] = {0};
    float output[OUTPUT_SIZE] = {0};

    forward(&model, input, output);

    printf("Forward pass completed!\n");
    return 0;
}
