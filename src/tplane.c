/**
 * File that contains the logic for tiled planes.
 * @author Marco Anton
 * @author Ben Dana
 */
#include "tplane.h"

static int tp_select(obj_t* obj);

obj_t* tplane_init(FILE* in, int objtype) {
    int rc = 0;
    obj_t* obj = plane_init(in, objtype);
    if (obj == NULL) {
        fprintf(stderr, "### in tplane.c\n\tplane_init:"
                        " error while initiating a plane.\n");
        return obj;
    }

    tplane_t* tplane = Malloc(sizeof(tplane_t));
    material_t* mat = Malloc(sizeof(material_t));
    plane_t* plane = obj->priv;
    plane->plane_priv = tplane;
    tplane->background = mat;

    rc += parse_doubles(in, tplane->xdir, "%lf%lf%lf", VECTOR_SIZE);
    rc += parse_doubles(in, tplane->size, "%lf%lf", VECTOR_SIZE - 1);
    rc += material_init(in, tplane->background);

    if (rc != 5*VECTOR_SIZE - 1) {
        fprintf(stderr, "### in tplane.c\n\ttplane_init:"
                        " error while parsing for tiled plane data.\n");
        free_tplane(obj);
        free(obj);
        obj = NULL;
    } else {
        unitvec(tplane->xdir, tplane->xdir);
        obj->hits = hits_tplane;
        obj->obj_dump = tplane_dump;
        obj->free_obj = free_tplane;
        obj->getamb = tplane_getamb;
        obj->getamb = tplane_getdiff;
        obj->getamb = tplane_getspec;
        double temp[VECTOR_SIZE];
        mat_proj(plane->normal, tplane->xdir, temp, VECTOR_SIZE);
        mat_rot(plane->normal, temp, *(tplane->rotmat));
    }

    return obj;
}

/**
 * dumps the information from a finite plane
 * @param out is an output stream.
 * @param obj is a tiled plane object to print.
 */
void tplane_dump(FILE* out, obj_t* obj) {
    plane_t* plane = obj->priv;
    tplane_t* tplane = plane->plane_priv;
    fprintf(out, "\nDumping objecto of type Tiled Plane:\n");
    material_dump(out, obj->material);
    fprintf(out, "\nTiled Plane data:\n");
    vecprn3(out, "\tnormal - ", plane->normal);
    vecprn3(out, "\tpoint - ", plane->point);
    vecprn3(out, "\tx dir - ", tplane->xdir);
    fprintf(out, "\tsize - \t\t%5.2lf, %5.2lf\n",
                    tplane->size[0], tplane->size[1]);
    fprintf(out, "Background color:\n");
    material_dump(out, tplane->background);
}

/**
 * Determines if a ray from base in the direction of dir hits an object.
 * @param base is the base of the ray.
 * @param dir is the direction of the ray.
 * @param obj is the object we are trying to hit.
 */
double hits_tplane(double* base, double* dir, obj_t* obj) {
    double t = -1;
fprintf(stdout, "hits_tplane\n");
    t = hits_plane(base, dir, obj);
    return t;
}

/**
 * gets the ambient from an object.
 * @param obj an object whose ambient we are trying to get.
 * @param amb a location to put the ambient light.
 */
void tplane_getamb(obj_t* obj, double* amb) {
    plane_t* plane = obj->priv;
    tplane_t* tplane = plane->plane_priv;

    if (tp_select(obj)) {
        cpy_vec(obj->material->ambient, amb, VECTOR_SIZE);
    } else {
        cpy_vec(tplane->background->ambient, amb, VECTOR_SIZE);
    }
}

/**
 * gets the diffuse from an object
 * @param obj an object whose diffuse we are trying to get.
 * @param diff a location to put the diffuse light.
 */
void tplane_getdiff(obj_t* obj, double* diff) {
    plane_t* plane = obj->priv;
    tplane_t* tplane = plane->plane_priv;

    if (tp_select(obj)) {
        cpy_vec(obj->material->diffuse, diff, VECTOR_SIZE);
    } else {
        cpy_vec(tplane->background->diffuse, diff, VECTOR_SIZE);
    }
}

/**
 * gets the specular from an object.
 * @param obj an object whose specular we are trying to get.
 * @param spec a location to put the specular light.
 */
void tplane_getspec(obj_t* obj, double* spec) {
    plane_t* plane = obj->priv;
    tplane_t* tplane = plane->plane_priv;

    if (tp_select(obj)) {
        cpy_vec(obj->material->specular, spec, VECTOR_SIZE);
    } else {
        cpy_vec(tplane->background->specular, spec, VECTOR_SIZE);
    }
}

/**
 * determines if the hitloc lies in a foreground or not.
 * @param obj is the object we are trying to determine.
 * @return 1 for foreground and 0 for background.
 */
static int tp_select(obj_t* obj) {
    plane_t* plane = obj->priv;
    tplane_t* tplane = plane->plane_priv;
    int relx = (int)obj->hitloc[0] / tplane->size[0];
    int rely = (int)obj->hitloc[1] / tplane->size[1];

    return relx + rely;
}

/**
 * frees a tplane by freeing the memory allocated in obj->priv->plane_priv and
 * calling plane's free function.
 * @param obj is an object ot free.
 */
void free_tplane(obj_t* obj) {
    plane_t* plane = obj->priv;
    tplane_t* tplane = plane->plane_priv;
    if(tplane != NULL) {
        free(tplane);
        free(tplane->background);
    }
    free_plane(obj);
}
