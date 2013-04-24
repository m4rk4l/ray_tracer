#ifndef FPLANE_H
#define FPLANE_H

#include "plane.h"

typedef struct fplane_type {
    double xdir[VECTOR_SIZE]; /* x axis direction */
    double size[VECTOR_SIZE - 1]; /* width x height */
    double rotmat[VECTOR_SIZE][VECTOR_SIZE]; /* rotation matrix */
    double lasthit[VECTOR_SIZE]; /* used for texures */
} fplane_t;

obj_t* fplane_init(FILE* in, int objtype);

void fplane_dump(FILE* out, obj_t* obj);

double hits_fplane(double* base, double* dir, obj_t* obj);

void fplane_getamb(obj_t* obj, double* amb);

void free_fplane(obj_t* plane);

#endif
