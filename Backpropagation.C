float mean_squared_error(Matrix *output, Matrix *target) {
    float loss = 0;
    for (int i = 0; i < output->rows * output->cols; i++) {
        loss += (output->data[i] - target->data[i]) * (output->data[i] - target->data[i]);
    }
    return loss / (output->rows * output->cols);
}
