#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

void preprocess_text(char *text) {
    // Convert to lowercase
    for (int i = 0; text[i]; i++) {
        text[i] = tolower(text[i]);
    }

    // Optional: Remove punctuation
    for (int i = 0; text[i]; i++) {
        if (ispunct(text[i])) {
            text[i] = ' ';
        }
    }
}

void tokenize(char *text, char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH], int *token_count) {
    char *token = strtok(text, " ");
    *token_count = 0;
    
    while (token != NULL) {
        strcpy(tokens[*token_count], token);
        (*token_count)++;
        token = strtok(NULL, " ");
    }
}

int get_token_id(char *token, char vocab[VOCAB_SIZE][MAX_TOKEN_LENGTH], int vocab_size) {
    for (int i = 0; i < vocab_size; i++) {
        if (strcmp(token, vocab[i]) == 0) {
            return i;
        }
    }
    return -1; // Token not found
}

int add_token_to_vocab(char *token, char vocab[VOCAB_SIZE][MAX_TOKEN_LENGTH], int *vocab_size) {
    if (*vocab_size < VOCAB_SIZE) {
        strcpy(vocab[*vocab_size], token);
        (*vocab_size)++;
        return *vocab_size - 1;
    }
    return -1; // Vocabulary full
}
