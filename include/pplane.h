#ifndef PPLANE_H
#define PPLANE_H

#include "plane.h"

void pplane1_amb(obj_t* obj, double* intensity);

static void (*plane_shaders[])(obj_t* obj, double* intensity) = {
    //pplane0_amb,
    pplane1_amb,
    //pplane2_amb
};
#define NUM_SHADERS sizeof(plane_shaders)/sizeof(void*)

obj_t* pplane_init(FILE* in, int objtype);
void pplane_dump(FILE* out, obj_t* obj);

#endif
