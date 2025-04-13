#include <stdio.h>
#include "training_accuracy.h"

int calculate_accuracy(Matrix* predictions, Matrix* targets) {
    int correct = 0;
    for (int i = 0; i < predictions->rows; i++) {
        int predicted_class = 0;
        float max_prob = predictions->data[i * predictions->cols];
        for (int j = 1; j < predictions->cols; j++) {
            if (predictions->data[i * predictions->cols + j] > max_prob) {
                max_prob = predictions->data[i * predictions->cols + j];
                predicted_class = j;
            }
        }
        if (predicted_class == (int)targets->data[i]) {
            correct++;
        }
    }
    return (correct * 100) / predictions->rows;
}

void log_accuracy(int epoch, int accuracy) {
    printf("Epoch %d: Accuracy = %d%%\n", epoch, accuracy);
}