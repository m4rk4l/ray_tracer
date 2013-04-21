#ifndef LIGHT_H
#define LIGHT_H

#include "object.h"
#include "veclib.h"

typedef struct light_type {
    double center[VECTOR_SIZE];
} light_t;

void diffuse_illumination(model_t *model, obj_t *hitobj,
 double *intensity);

int process_light(list_t *lst, obj_t *hitobj, obj_t *lobj, 
 double *ivec);
#endif
