#include "sphere.h"

static void psphere0_amb(obj_t* obj, double* intensity);
static void psphere1_amb(obj_t* obj, double* intensity);
//static void psphere2_amb(obj_t* obj, double* intensity);

static void (*sphere_shaders[])(obj_t* obj, double* intensity) = {
    psphere0_amb,
    psphere1_amb//,
    //psphere2_amb
};

/**
 * Initiates a procedural sphere by calling its parent object
 * @param in an input stream
 * @param objtype the type of this object should be P_SHPERE
 * @return returns a newly created object or null if there exist a parsing
 * error.
 */
obj_t* psphere_init(FILE* in, int objtype) {
    int rc = 0;
    int ndx;
    obj_t* new = sphere_init(in, objtype);

    if(new == NULL) {
        fprintf(stderr, "### in psphere_init\n\t"
                        "error while initiating a sphere\n");
        return new;
    }

    rc = parse_ints(in, &ndx, "%d", 1);
    int num_shaders = sizeof(sphere_shaders)/sizeof(void*);
    if (rc == 0 && ndx <= num_shaders) {
        //sphere_t* spehere = new->priv;
        //sphere->sphere_priv = NULL;
        new->obj_dump = psphere_dump;
        new->getamb = sphere_shaders[ndx];
        new->free_obj = free_psphere;
    } else {
        fprintf(stderr, "### in psphere_init\n\t"
                        "error with either parsing or index is invalid\n");
        free_psphere(new);
        new = NULL;
    }

    return new;
}

/**
 * a dumper function for a pshpere.
 * @param out an output stream.
 * @param obj an object to print. if calling this func, object must be
 * a psphere.
 */
void psphere_dump(FILE* out, obj_t* obj) {
    sphere_t* sphere = (sphere_t*)obj->priv;

    fprintf(out, "\nDumping objecto of type Procedural Sphere:\n");
    material_dump(out, obj->material);
    /** object specific */
    fprintf(out, "\nProcedural sphere data:\n");
    vecprn3(out, "\tcenter - ", sphere->center);
    fprintf(out, "\tradius - \t%3.6lf\n", sphere->radius);
}

/**
 *
 */
static void psphere0_amb(obj_t* obj, double* value) {
    double vec[3];
    sphere_t* sphere = (sphere_t*)obj->priv;
    int isum;
    double sum;

    cpy_vec(value, obj->material->ambient, SIZE);
    diff3(sphere->center, obj->hitloc, vec);

    sum = 1000 + vec[0] * vec[1] * vec[1]/100 + vec[0] * vec[1]/100;
    isum = sum;

    if (isum & 1) {
        value[0] = 0; // zap red
    } else {
        value[2] = 0; // zap blue
    }
}

/**
 *
 */
static void psphere1_amb(obj_t* obj, double* value) {
    double vec[3];
    sphere_t* sphere = (sphere_t*)obj->priv;

    cpy_vec(value, obj->material->ambient, SIZE);
    diff3(sphere->center, obj->hitloc, vec);

    double v1 = (vec[0]/sqrt(vec[0] * vec[0] + vec[1] * vec[1]));
    double t1 = acos(v1);

    if(vec[1] < 0) {
        t1 = 2 * PI - t1;
    }

    value[0] *= (1 + cos(2 * t1));
    value[1] *= (1 + cos(2 * t1 + 2 * PI / 3));
    value[2] *= (1 + cos(2 * t1 + 4 * PI / 3));
}

/**
 *
static void psphere2_amb(obj_t* obj, double* value) {
}
 */

/**
 * frees a psphere object
 * @param obj is an object to free.
 */
void free_psphere(obj_t* obj) {
    free_sphere(obj);
}
