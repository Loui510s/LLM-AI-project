#include <stdlib.h>
#include <time.h>
#include "model.h"
#include "matrix.h"

// Random float between -1 and 1
float randf() {
    return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}


Model* create_model(int input_size, int hidden_size, int output_size) {
    srand((unsigned int)time(NULL)); // Seed random only once

    Model* model = malloc(sizeof(Model));
    model->W1 = create_matrix(input_size, hidden_size);
    model->b1 = create_matrix(1, hidden_size);
    model->W2 = create_matrix(hidden_size, output_size);
    model->b2 = create_matrix(1, output_size);

    // Fill matrices with random weights
    for (int i = 0; i < input_size * hidden_size; i++) {
        model->W1->data[i] = randf();
    }
    for (int i = 0; i < hidden_size; i++) {
        model->b1->data[i] = randf();
    }
    for (int i = 0; i < hidden_size * output_size; i++) {
        model->W2->data[i] = randf();
    }
    for (int i = 0; i < output_size; i++) {
        model->b2->data[i] = randf();
    }

    return model;
}


void free_model(Model* model) {
    free_matrix(model->W1);
    free_matrix(model->b1);
    free_matrix(model->W2);
    free_matrix(model->b2);
    free(model);
}

Matrix* model_forward(Model* model, Matrix* input) {
    Matrix* z1 = mat_mul(input, model->W1);
    for (int i = 0; i < z1->rows * z1->cols; i++) {
        z1->data[i] += model->b1->data[i % model->b1->cols];
    }

    Matrix* a1 = mat_relu(z1);
    free_matrix(z1);

    Matrix* z2 = mat_mul(a1, model->W2);
    free_matrix(a1);

    for (int i = 0; i < z2->rows * z2->cols; i++) {
        z2->data[i] += model->b2->data[i % model->b2->cols];
    }

    Matrix* output = mat_softmax(z2);
    free_matrix(z2);

    return output;
}
#include <stdio.h>

void save_matrix(FILE* f, Matrix* m) {
    fwrite(&m->rows, sizeof(int), 1, f);
    fwrite(&m->cols, sizeof(int), 1, f);
    fwrite(m->data, sizeof(float), m->rows * m->cols, f);
}

Matrix* load_matrix(FILE* f) {
    int rows, cols;
    fread(&rows, sizeof(int), 1, f);
    fread(&cols, sizeof(int), 1, f);
    Matrix* m = create_matrix(rows, cols);
    fread(m->data, sizeof(float), rows * cols, f);
    return m;
}

void save_model(Model* model, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) return;
    save_matrix(f, model->W1);
    save_matrix(f, model->b1);
    save_matrix(f, model->W2);
    save_matrix(f, model->b2);
    fclose(f);
}

Model* load_model(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;
    Model* model = malloc(sizeof(Model));
    model->W1 = load_matrix(f);
    model->b1 = load_matrix(f);
    model->W2 = load_matrix(f);
    model->b2 = load_matrix(f);
    fclose(f);
    return model;
}
