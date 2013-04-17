#include "pplane.h"

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
    if (rc == 0 && ndx <= NUM_SHADERS) {
        new->obj_dump = pplane_dump;
        new->getamb = plane_shaders[ndx];// maybe add ndx to plane data
        new->free_obj = free_pplane;
    } else {
        fprintf(stderr, "### in pplane_init\n\t"
                        "error with either parsing or ndx is invalid\n");
        new->free_obj(new);
        new = NULL;
    }

    return new;
}

/**
 * A dumper function for pplane.
 * @param out an output stream.
 * @param obj an object to print. if calling this func, obj must be a pplane.
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
 * a function that changes the ambient lightning.
 * @param obj is an object whose ambient we are changing.
 * @param value is apointer to an array?
 */
void pplane0_amb(obj_t* obj, double* value) {
}

/**
 * a function that changes the ambient lightning.
 * @param obj is an object whose ambient we are changing.
 * @param value is apointer to an array?
 */
void pplane1_amb(obj_t* obj, double* value) {
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
    vecprn3(stderr, "value: ", value);
}

/**
 * a function that changes the ambient lightning.
 * @param obj is an object whose ambient we are changing.
 * @param value is apointer to an array?
 */
void pplane2_amb(obj_t* obj, double* value) {
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
 * frees a pplane object.
 * @param obj is an objct to free
 */
void free_pplane(obj_t* obj) {
    free_plane(obj);
}
