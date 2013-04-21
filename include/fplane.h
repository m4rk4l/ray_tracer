#ifndef FPLANE_H
#define FPLANE_H

#include "plane.h"

typedef struct fplane_type {
    double xdir[3]; /* x axis direction */
    double size[2]; /* width x height */
    double rotmat[3][3]; /* rotation matrix */
    double lasthit[3]; /* used for texures */
} fplane_t;

obj_t* fplane_init(FILE* in, int objtype);

void fplane_dump(FILE* out, obj_t* obj);

double hits_fplane(double* base, double* dir, obj_t* obj);

void fplane_getamb(obj_t* obj, double* amb);

/**
void fplane_getdiff(...);

void fplane_getspec(...);
 */

void free_fplane(obj_t* plane);

#endif
