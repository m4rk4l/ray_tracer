#ifndef ILLUMINATE_H
#define ILLUMINATE_H

#include "model.h"
#include "object.h"

void diffuse_illumination(model_t* model, obj_t* hitobj, double* intensity);

int process_light(list_t* lst, obj_t* hitobj, obj_t* lobj, double* ivec);
#endif
