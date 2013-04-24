#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "veclib.h"

typedef struct plane_type {
    double point[VECTOR_SIZE]; /** a point on the plane */
    double normal[VECTOR_SIZE]; /** a normal to the plane */
    
    void* plane_priv;
} plane_t;

obj_t* plane_init(FILE* in, int objtype);

void plane_dump(FILE* out, obj_t* obj);

double hits_plane(double* base, double* dir, obj_t* obj);

void plane_getamb(obj_t* obj, double* amb);

void plane_getdiff(obj_t* obj, double* diffuse);

void plane_getspec(obj_t* obj, double* specular);

void free_plane(obj_t* plane);

/** functions for pplanes  */
obj_t* pplane_init(FILE* in, int objtype);
void free_pplane(obj_t* pplane);
void pplane_dump(FILE* out, obj_t* obj);
#endif
