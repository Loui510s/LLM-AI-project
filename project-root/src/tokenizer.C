#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

int* tokenize(const char* text, int* out_length) {
    int len = strlen(text);
    int* tokens = (int*)malloc(sizeof(int) * len);

    for (int i = 0; i < len; i++) {
        tokens[i] = (int)text[i]; // very basic: each char becomes its ASCII code
    }

    *out_length = len;
    return tokens;
}

void free_tokens(int* tokens) {
    free(tokens);
}
