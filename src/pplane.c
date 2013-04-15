
#include "pplane.h"

/**
 * Initiates a plane by calling its parent object.
 * @param in an input stream
 * @param objtype the tpe of this object. should be P_PLANE
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

    if (rc == 0 || ndx < NUM_SHADERS) {
        new->getamb = plane_shaders[ndx];// maybe add ndx to plane data
        new->free_obj = free_pplane;
    } else {
        fprintf(stderr, "### in pplane_init\n\t"
                        "error with either parsing or ndx is invalid\n");
        new->free_obj(new);
        new = NULL;
        return new;
    }

    return new;
}

/**
 * calls plane dump and it prints the pplane index.
 * @param out output stream
 * @param obj pointer containing info about pplane object.
 */
void pplane_dump(FILE* out, obj_t* obj) {
    fprintf(out, "\nDumping object of type pplane");
    plane_dump(out, obj);
    fprintf(out, "\tshader index: \n");// how to get the index?
}

/**
 *
 */
void pplane1_amb(obj_t* obj, double* value) {
}

/**
 *
 */
void free_pplane(obj_t* obj) {
    free_plane(obj);
}
