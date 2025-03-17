#ifndef TOKENIZER_H
#define TOKENIZER_H

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 50
#define VOCAB_SIZE 1000

void preprocess_text(char *text);
void tokenize(char *text, char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH], int *token_count);
int get_token_id(char *token, char vocab[VOCAB_SIZE][MAX_TOKEN_LENGTH], int vocab_size);
int add_token_to_vocab(char *token, char vocab[VOCAB_SIZE][MAX_TOKEN_LENGTH], int *vocab_size);

#endif // TOKENIZER_H