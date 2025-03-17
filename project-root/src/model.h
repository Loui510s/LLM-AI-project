#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

typedef struct {
    Matrix weights_ih;
    Matrix weights_ho;
} Model;

#endif // MODEL_H