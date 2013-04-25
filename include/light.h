#ifndef LIGHT_H
#define LIGHT_H

#include "object.h"
#include "veclib.h"

typedef struct light_type {
    double center[VECTOR_SIZE];
} light_t;

obj_t* light_init(FILE* in, int objtype);
void light_dump(FILE* out, obj_t* obj);
void free_light(obj_t* obj);
void light_getemiss(obj_t* obj, double* emiss);
#endif
