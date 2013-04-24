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
obj_t* light_init(FILE* in, int objtype);
void light_dump(FILE* out, obj_t* obj);
void free_light(obj_t* obj);
#endif
