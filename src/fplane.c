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
                        " error while initiating a plane\n");
        return obj;
    }

    fplane_t* fplane = Malloc(sizeof(fplane_t));
    plane_t* plane = obj->priv;
    plane->plane_priv = fplane;

    rc += parse_doubles(in, fplane->xdir, "%lf%lf%lf", VECTOR_SIZE);
    rc += parse_doubles(in, fplane->size, "%lf%lf", VECTOR_SIZE - 1);

    if (rc != VECTOR_SIZE + 2) {// read five things
        fprintf(stderr, "### in fplane.c\n\tfplane_init: error while"
                        " parsing for finite plane data.\n");
        free_fplane(obj); // frees a plane object.
        free(obj);
        obj = NULL;
    } else {
        unitvec(fplane->xdir, fplane->xdir);
        obj->hits = hits_fplane;
        obj->obj_dump = fplane_dump;
        obj->free_obj = free_fplane;
        //project xdir onto infinite plane
        double temp[VECTOR_SIZE];
        mat_proj(plane->normal, fplane->xdir, temp, VECTOR_SIZE);
        //compute required rotation matrix
        mat_rot(plane->normal, temp, *(fplane->rotmat));
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
    fprintf(out, "\nFinite Plane data:\n");
    vecprn3(out, "\tnormal - ", plane->normal);
    vecprn3(out, "\tpoint - ", plane->point);
    vecprn3(out, "\tx dir - ", fplane->xdir);
    fprintf(out, "\tsize -\t\t%5.2lf, %5.2lf\n",
                    fplane->size[0], fplane->size[1]);
}

/**
 * determines if a ray from base in the direction of dir hits an object
 * obj.
 * @param base is the base of the ray
 * @param dir is the direction of the ray
 * @param obj is the object we are trying to hit.
 */
double hits_fplane(double* base, double* dir, obj_t* obj) {
    double t;
    double newhit[SIZE];
    plane_t* plane = obj->priv;
    fplane_t* fplane = plane->plane_priv;
    t = hits_plane(base, dir, obj);
    if (t > 0) {
        //transform coordinates
        diff3(plane->point, obj->hitloc, newhit);
        mat_xform(*(fplane->rotmat), newhit, newhit, VECTOR_SIZE);
        //do tests.
        if ((newhit[0] > fplane->size[0]) || (newhit[0] < 0.0)) {
            t = -1;// return miss
        }
        if ((newhit[1] > fplane->size[1]) || (newhit[1]) < 0.0) {
            t = -1;// return miss
        }
    }
    return t;
}

/**
 * frees a fplane by freeing the memory allocated in obj->priv->plane_priv and
 * calling plane's free function.
 * @param obj is an object to free.
 */
void free_fplane(obj_t* obj) {
    plane_t* plane = obj->priv;
    fplane_t* fplane = plane->plane_priv;
    if (fplane != NULL) {
        free(fplane);
    }
    free_plane(obj);
}
