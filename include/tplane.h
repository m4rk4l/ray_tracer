#include "plane.h"

typedef struct tplane_type {
    double xdir[VECTOR_SIZE];
    double size[VECTOR_SIZE - 1];
    double rotmat[VECTOR_SIZE][VECTOR_SIZE];
    material_t* background;
} tplane_t;

obj_t* tplane_init(FILE* in, int objtype);
void tplane_dump(FILE* out, obj_t* obj);
double hits_tplane(double* base, double* dir, obj_t* obj);
void tplane_getamb(obj_t* obj, double* amb);
void tplane_getdiff(obj_t* obj, double* diff);
void tplane_getspec(obj_t* obj, double* spec);
void free_tplane(obj_t* plane);
