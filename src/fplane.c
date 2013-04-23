/**
 * file that contains the loginc to create a finite plane.
 * @author Marco Anton
 * @author Ben Dana
 */
#include "fplane.h"

/**
 * Initiates a finite plane by calling its parent plane.
 * @param in a stream to read from.
 * @param objtype is the object type of a finite plane.
 */
obj_t* fplane_init(FILE* in, int objtype) {
    int rc = 0;
    obj_t* obj = plane_init(in, objtype);
    if (obj == NULL) {
        fprintf(stderr, "### in fplane.c\n\tfplane_init:"
                        "error while initiating a plane\n");
        return obj;
    }

    fplane_t* fplane = Malloc(sizeof(fplane_t));
    plane_t* plane = obj->priv;
    plane->plane_priv = fplane;

    rc += parse_ints(in, NULL, "", 0);//parse an empty line
    rc += parse_doubles(in, fplane->xdir, "%lf%lf%lf", VECTOR_SIZE);
    unitvec(fplane->xdir, fplane->xdir);
    rc += parse_doubles(in, fplane->size, "%lf%lf", VECTOR_SIZE - 1);

    if (rc != 0) {
        fprintf(stderr, "### in fplane.c\n\tfplane_init: error while"
                        " parsing for finite plane data.\n");
        free_fplane(obj);; // frees a plane object.
        free(obj);
        obj = NULL;
    } else {
        obj->hits = hits_fplane;
        obj->getamb = fplane_getamb;
        //obj->getdiff = fplane_getdiff;
        //obj->getspec = fplane_getspec;
        obj->obj_dump = fplane_dump;
        obj->free_obj = free_fplane;
        //mat_proj(plane->normal, fplane->xdir, fplane->rotmat);
        //project xdir onto infinite plane
        //compute required rotation matrix
    }

    return obj;
}

/**
 * dumps the information from a finite plane.
 * @param out is an output stream.
 * @param obj is a finite plane object to print.
 */
void fplane_dump(FILE* out, obj_t* obj) {
    plane_t* plane = (plane_t*)obj->priv;
    fplane_t* fplane = (fplane_t*)plane->plane_priv;
    fprintf(out, "\nDumping object of type  Finite Plane:\n");
    material_dump(out, obj->material);
    fprintf(out, "\nPlane data:\n");
    vecprn3(out, "\tnormal - ", plane->normal);
    vecprn3(out, "\tpoint - ", plane->point);
    vecprn3(out, "\tx dir - ", fplane->xdir);
    fprintf(out, "\tsize -\t\t%5.2lf, %5.2lf\n",
                    fplane->size[0], fplane->size[1]);
}

double hits_fplane(double* base, double* dir, obj_t* obj) {
    return -1;
}

void fplane_getamb(obj_t* obj, double* amb) {
}

/**
void fplane_getdiff(...);

void fplane_getspec(...);
 */

void free_fplane(obj_t* plane) {
}
