#ifndef MODEL_H
#define MODEL_H

#include "projection.h"
#include "list.h"
#include "sphere.h"
#include "plane.h"

/** Define a structure for our model and call it model_t */
typedef struct model_type {
    proj_t* proj;
    list_t* lights;
    list_t* scene;
} model_t;

int model_init(FILE* in, model_t* model);

void model_dump(FILE* out, model_t* model);

#endif
