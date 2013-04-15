#ifndef OBJECT_H
#define OBJECT_H

/** object types */
#define FIRST_TYPE   10
#define LIGHT        10
#define SPOTLIGHT    11
#define PROJECTOR    12
#define SPHERE       13
#define PLANE        14
#define FINITE_PLANE 15
#define TILED_PLANE  16
#define TEX_PLANE    17
#define REF_SPHERE   18
#define P_SPHERE     19
#define P_PLANE      20
#define PARABOLOID   21
#define CYLINDER     22
#define CONE         23
#define HYPERBOLOID  24
#define LAST_TYPE    25
#define LAST_LIGHT   12

#define TEX_FIT       1
#define TEX_TILE      2

#include "Malloc.h"
#include "material.h"

typedef struct obj_type {
    struct obj_type* next; /** Next object in list */
    int objid;             /** Numeric serial # for debug */
    int objtype;           /** Type code (14 -> Plane) */

    /** hits function */
    double (*hits)(double* base, double* dir, struct obj_type* obj);

    /** Optional plugins for retrieval of reflectivity */
    /** useful for the ever-popular tiled floor */
    void (*getamb)(struct obj_type* obj, double* num);
    /**
    void (*getdiff)(struct obj_type* obj, double* num);
    void (*getspec)(struct obj_type* obj, double* num);
    */

    /** Relectivity for reflective objects */
    material_t* material;

    /** These fields used only in illuminating objects (lights) */
    void (*getemiss)(struct obj_type* obj, double* num);
    double emmissivity[3]; /** for lights */
    void* priv; /** Private type-dependent data */

    double hitloc[VECTOR_SIZE]; /** last hit point */
    double normal[VECTOR_SIZE]; /** normal at hit point */

    void (*free_obj)(struct obj_type* obj);

} obj_t;

obj_t* object_init(FILE* in, int objtype);

#endif
