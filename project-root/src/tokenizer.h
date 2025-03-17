#ifndef TOKENIZER_H
#define TOKENIZER_H

#define VOCAB_SIZE 1000 // Define VOCAB_SIZE with an appropriate value
#define MAX_TOKEN_LENGTH 50 // Define MAX_TOKEN_LENGTH with an appropriate value
#define MAX_TOKENS 100 // Define MAX_TOKENS with an appropriate value

void preprocess_text(const char *input, char *output);
void tokenize(const char *input, char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH], int *token_count);
int get_token_id(const char *token, char vocab[VOCAB_SIZE][MAX_TOKEN_LENGTH], int vocab_size);
int add_token_to_vocab(const char *token, char vocab[VOCAB_SIZE][MAX_TOKEN_LENGTH], int *vocab_size);

#endif // TOKENIZER_H
