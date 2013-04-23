#ifndef ILLUMINATE_H
#define ILLUMINATE_H

#include "model.h"
#include "object.h"

void diffuse_illumination(model_t* model, obj_t* hitobj, double* intensity);

#endif
