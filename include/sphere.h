#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "veclib.h"

typedef struct sphere_type {
    double center[VECTOR_SIZE]; /** center of the sphere */
    double radius; /** radius of sphere */
} sphere_t;

obj_t* sphere_init(FILE* in, int objtype);

void sphere_dump(FILE* out, obj_t* obj);
double sphere_hits(double* base, double* dir, struct obj_type* obj);
void sphere_getamb(obj_t *obj, double* amb);
void sphere_getdiff(obj_t *obj, double* diff);
void sphere_getspec(obj_t *obj, double* spec);
void free_sphere(obj_t* sphere);

/** functions for pspheres  */
obj_t* psphere_init(FILE* in, int objtype);
void free_psphere(obj_t* psphere);
void psphere_dump(FILE* out, obj_t* obj);
#endif
