#include "plane.h"
static void pplane0_amb(obj_t* obj, double* intensity);
static void pplane1_amb(obj_t* obj, double* intensity);
static void pplane2_amb(obj_t* obj, double* intensity);
static void pplane3_amb(obj_t* obj, double* intensity);
/* The following is a pointer to a list of ambient procedural shaders */
static void (*plane_shaders[])(obj_t* obj, double* intensity) = {
    pplane0_amb,
    pplane1_amb,
    pplane2_amb,
    pplane3_amb
};

/**
 * Initiates a plane by calling its parent object.
 * @param in an input stream
 * @param objtype the tpe of this object. should be P_PLANE
 * @return returns an newly created object or null if there exist a parsing
 * error.
 */
obj_t* pplane_init(FILE* in, int objtype) {
    int rc = 0;
    int ndx;
    obj_t* new = plane_init(in, objtype);

    if(new == NULL) {
        fprintf(stderr, "### in pplane_init\n\t"
                        "error initiating a plane.\n");
        return new;
    }

    rc = parse_ints(in, &ndx, "%d", 1);
    int num_shaders = sizeof(plane_shaders)/sizeof(void*);
    if (rc == 1 && ndx <= num_shaders) {
        plane_t* plane = new->priv;
        plane->plane_priv = NULL;
        new->obj_dump = pplane_dump;
        new->getamb = plane_shaders[ndx];
        new->free_obj = free_pplane;
    } else {
        fprintf(stderr, "### in pplane_init\n\t"
                        "error with either parsing or ndx is invalid\n");
        free_pplane(new);
        new = NULL;
    }

    return new;
}

/**
 * A dumper function for pplane;
 * If calling this func, obj must be a pplane.
 * @param out an output stream.
 * @param obj an object to print.
 */
void pplane_dump(FILE* out, obj_t* obj) {
    plane_t* aplane = (plane_t*)obj->priv;

    fprintf(out, "\nDumping object of type Procedural Plane:\n");

    material_dump(out, obj->material);
    /** object specific */
    fprintf(out, "\nPlane data:\n");
    vecprn3(out, "\tnormal - ", aplane->normal);
    vecprn3(out, "\tpoint - ", aplane->point);
}

/**
 * Function that changes the ambient lightning in a geometric way.
 * @param obj is an object whose ambient we are changing.
 * @param value is apointer to an array?
 */
static void pplane1_amb(obj_t* obj, double* value) {
    double vec[3];
    plane_t* p = (plane_t*)obj->priv;
    int isum;
    double sum;

    cpy_vec(value, obj->material->ambient, SIZE);
    diff3(p->point, obj->hitloc, vec);

    sum = 1000 + vec[0] * vec[1] * vec[1]/100 + vec[0] * vec[1]/100;
    isum = sum;

    if (isum & 1) {
        value[0] = 0; // zap red
    } else {
        value[2] = 0; // zap blue
    }
}

/**
 * Function that changes the ambient lightning in a multi-colored 
 * spherical shape.
 * @param obj is an object whose ambient we are changing.
 * @param value is a pointer to a vector destination
 */
static void pplane2_amb(obj_t* obj, double* value) {
    double vec[3];
    plane_t* p = (plane_t*)obj->priv;

    cpy_vec(value, obj->material->ambient, SIZE);
    diff3(p->point, obj->hitloc, vec);
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
 * Function that changes the ambient lightning to create 
 * stripes on a plane.
 * @param obj is an object whose ambient we are changing.
 * @param value is a pointer to a vector destination.
 */
static void pplane3_amb(obj_t* obj, double* value) {
    double vec[3];
    plane_t* p = (plane_t*)obj->priv;
    int isum;
    double sum;

    cpy_vec(value, obj->material->ambient, SIZE);
    diff3(p->point, obj->hitloc, vec);

    sum = 1000 + vec[0] - vec[1];
    isum = sum;

    if (isum & 1) {
        value[0] = 1;
    } else {
        value[2] = 1;
    }

}
/**
 * Function that changes the ambient lightning to a checkerboard.
 * @param obj is an object whose ambient we are changing.
 * @param value is a pointer to a vector destination.
 */
static void pplane0_amb(obj_t* obj, double* value) { //checkerboard
    double vec[3];
    plane_t* p = (plane_t*)obj->priv;
    int isum;

    cpy_vec(value, obj->material->ambient, SIZE);
    diff3(p->point, obj->hitloc, vec);

    int x = 1000 + vec[0];
    int y = 1000 + vec[1];
    isum = x + y;
    if (isum & 1) {
        value[0] = 1;
    }
}

/**
 * Frees a procedural plane object.
 * @param obj is an object to freed.
 */
void free_pplane(obj_t* obj) {
    free_plane(obj);
}
