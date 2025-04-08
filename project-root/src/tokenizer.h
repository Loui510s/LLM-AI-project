#ifndef TOKENIZER_H
#define TOKENIZER_H

int* tokenize(const char* text, int* out_length); // Returns array of token IDs
void free_tokens(int* tokens);

#endif
