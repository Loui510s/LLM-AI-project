#ifndef TRAINING_ACCURACY_H
#define TRAINING_ACCURACY_H

#include "matrix.h"

int calculate_accuracy(Matrix* predictions, Matrix* targets);
void log_accuracy(int epoch, int accuracy);

#endif