#include "plane.h"

/** forward declarations */
static void plane_hitloc(double* base, double* dir, double dist,
                                                                double* dest);

/**
 * initializes a plane...
 * @param in is an imput to parse.
 * @param objtype is an object type for this object. should be 14 since its a
 * plane.
 */
obj_t* plane_init(FILE* in, int objtype) {
    int rc = 0;
    obj_t* obj = object_init(in, objtype);
    plane_t* plane = (plane_t*)Malloc(sizeof(plane_t));

    if(obj == NULL) {// if object_init fails
        fprintf(stderr, "### in plane.c\n\t"
                        "error while parsing for properties on"
                        " plane object\n");
        free(plane);
        return obj;
    }

    obj->priv = plane;// need to cast to void?
    rc = parse_ints(in, NULL, "", 0);// before getting plane info we expect
                                     // an empty line.
    rc += parse_doubles(in, plane->normal, "%lf%lf%lf", VECTOR_SIZE);
    rc += parse_doubles(in, plane->point, "%lf%lf%lf", VECTOR_SIZE);

    if (rc != 0) {
        fprintf(stderr, "###in plane.c\n\tplane_init: error while parsing"
                        " plane object.\n");
        free(obj->priv);
        free(obj);
        obj = NULL;
    }

    //initialize object specific funcs
    obj->hits = hits_plane;
    obj->getamb = plane_getamb;
    //obj->getdiff = plane_getdiff;
    //obj->getspec = plane_getspec;
    obj->obj_dump = plane_dump;
    obj->free_obj = free_plane;

    return obj;
}

/**
 * dumps obj information
 * @param out is a file to write to.
 * @param obj is the obj that we need info from.
 */
void plane_dump(FILE* out, obj_t* obj) {
    plane_t* aplane = (plane_t*)obj->priv;

    fprintf(out, "\nDumping object of type Plane:\n");

    material_dump(out, obj->material);
    /** object specific */
    fprintf(out, "\nPlane data:\n");
    vecprn3(out, "\tnormal - ", aplane->normal);
    vecprn3(out, "\tpoint - ", aplane->point);
}

/**
 * checks if a base in the direction of dir hits an object obj.
 * @param base the base of the vp (not the view_point necessarily)
 * @param obj an object to check
 */
double hits_plane(double* base, double* dir, obj_t* obj) {
    double dist = -1;
    plane_t* plane = (plane_t*)obj->priv;

    //normal dot dir
    double normal_dot_dir = dot3(plane->normal, dir);
#ifdef DBG_HITS_PLANE
    fprintf(stderr, "\nN dot (P-Q): %5.2lf\n", normal_dot_dir);
#endif
    if (normal_dot_dir != 0) {
        //'solving for t'
        dist = (dot3(plane->normal, plane->point) -
                dot3(plane->normal, base)) / normal_dot_dir;
#ifdef DBG_HITS_PLANE
    fprintf(stderr, "\nt_h = (N dot Q - N dot V)/(N dot D):\n"
                      "t_h = (%5.2lf - %5.2lf)/(%5.2lf)\n"
                      "t_h = (%5.2lf)/(%5.2lf)\n"
                      "t_h = %5.2lf\n",
                      dot3(plane->normal, plane->point),
                      dot3(plane->normal, base), normal_dot_dir,
                      dot3(plane->normal, plane->point) -
                                            dot3(plane->normal, base),
                      normal_dot_dir,
                      dist);
#endif
    	plane_hitloc(base, dir, dist, obj->hitloc);
        // checking special cases of dist.
        double hz = obj->hitloc[2];
#ifdef DBG_HITS_PLANE
		fprintf(stderr, "\nhz = %lf\n", hz);
#endif
        if (dist < ALMOST_ZERO || hz > ALMOST_ZERO) {
            dist = -1;
        } else { // otherwise, set hitloc and normal
            obj->normal[0] = plane->normal[0];
            obj->normal[1] = plane->normal[1];
            obj->normal[2] = plane->normal[2];
            //memcpy(obj->normal, plane->normal, VECTOR_SIZE);
        }
    }
    return dist;
}

/**
 * gets the ambient light from an object and puts it into amb
 * @param obj a pointer to an object.
 * @param amb a pointer to the return value.
 */
void plane_getamb(obj_t* obj, double* amb) {
    amb[0] = obj->material->ambient[0];
    amb[1] = obj->material->ambient[1];
    amb[2] = obj->material->ambient[2];
}

/**
 * finds the hit location given by H = base + dist(dir).
 * @param base represents the start of the ray.
 * @param dir is a unit vector representing the direction of base.
 * @param dist is the distance of a hit location.
 * @param dest is where to store the hit location
 */
static void plane_hitloc(double* base, double* dir, double dist,
                                                            double* dest) {
    double scalled[3];
    scale3(dist, dir, scalled);
    sum3(base, scalled, dest);
}

/**
 * Frees the data related to only a plane.
 * @param obj is a pointer to an object that contains a plane in its
 * priv data.
 */
void free_plane(obj_t* obj) {
    plane_t* plane = obj->priv;
    free(obj->material);
    free(plane);
}
