#include "matrix.h"

float mean_squared_error(Matrix* predictions, Matrix* targets) {
    float loss = 0.0f;
    for (int i = 0; i < predictions->rows; i++) {
        for (int j = 0; j < predictions->cols; j++) {
            float diff = predictions->data[i * predictions->cols + j] - targets->data[i * targets->cols + j];
            loss += diff * diff;
        }
    }
    return loss / predictions->rows;
}