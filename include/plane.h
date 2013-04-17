#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "veclib.h"

/** ################# INFINITE PLANES #######################  */
typedef struct plane_type {
    double point[VECTOR_SIZE]; /** a point on the plane */
    double normal[VECTOR_SIZE]; /** a normal to the plane */
} plane_t;

obj_t* plane_init(FILE* in, int objtype);

void plane_dump(FILE* out, obj_t* obj);

double hits_plane(double* base, double* dir, obj_t* obj);

void plane_getamb(obj_t* obj, double* amb);

/**
void plane_getdiff(...);

void plane_getspec(...);
 */

void free_plane(obj_t* plane);

/** ################# PROCEDURAL PLANES #######################  */

void pplane0_amb(obj_t* obj, double* intensity);
void pplane1_amb(obj_t* obj, double* intensity);
void pplane2_amb(obj_t* obj, double* intensity);

static void (*plane_shaders[])(obj_t* obj, double* intensity) = {
    pplane0_amb,
    pplane1_amb,
    pplane2_amb
};
#define NUM_SHADERS sizeof(plane_shaders)/sizeof(void*)

obj_t* pplane_init(FILE* in, int objtype);
void pplane_dump(FILE* out, obj_t* obj);
void free_pplane(obj_t* obj);

/** ################# FINITE PLANES #######################  */
#endif
