/**
 * This file defines the functions for a sphere object.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#ifndef SPHERE_C
#define SPHERE_C

#include "sphere.h"

/** function declarations */
static void sphere_hitloc(double* base, double* dir, double dist,double* dest);

/**
 * This fuction initializes a sphere object.
 *
 * @param in, is the standard input.
 * @param objtype, is the value for the type of object.
 * @return obj is the newly created object superclass.
 */
obj_t* sphere_init(FILE* in, int objtype) {
    int rc = 0;
    double radius = 0;
    obj_t* obj = object_init(in, objtype);
    sphere_t* sphere = (sphere_t*)Malloc(sizeof(sphere_t));

    if(obj == NULL) {// if object_init fails
        fprintf(stderr, "### in sphere.c\n\t"
                        "error while parsing for properties on"
                        " sphere object\n");
        return obj;
    }

    obj->priv = sphere;// need to cast to void?
    obj->hits = sphere_hits; //points to function now?
    obj->getamb = sphere_getamb; //points to function now?

    rc = parse_ints(in, NULL, "", 0);// before getting plane info we expect
                                  //an empty line.
    rc += parse_doubles(in, sphere->center, "%lf%lf%lf", VECTOR_SIZE);
    rc += parse_doubles(in, &radius, "%lf", 1);

    if (radius != -1) {
        sphere->radius = radius;
    }

    if (rc != 0) {
        fprintf(stderr, "###in sphere.c\n\t"\
                        "sphere_init: error while parsing"
                        " sphere object.\n");
        obj = NULL;
    }

    return obj;
}
/**
 * Dumps information related to the sphere object to standard error.
 *
 * @param out is a file to write to.
 * @param obj is the obj that we need info from.
 * @return rc
 */
int sphere_dump(FILE* out, obj_t* obj) {
    int rc = 0;
    sphere_t* asphere = (sphere_t*)obj->priv;

    fprintf(out, "\nDumping object of type Sphere:\n");

    material_dump(out, obj->material);
    /** object specific */
    fprintf(out, "\nSphere data:\n\tcenter -");
    printN(out, asphere->center);
    fprintf(out, "\tradius - \t%3.6lf\n", asphere->radius);

    return rc;
}

/**
 * Checks to see if a ray will his the sphere object.
 * @param base is the location of the viewer or previous hit.
 * @param dir is a unit vector in the direction of object.
 * @param last_hit obj that reflecteddot3 this ray or NULL.
 * @return dist, the distance between the sphere and location of ray.
 */
double sphere_hits(double* base, double* dir, obj_t* obj) {
    double dist = -1;
    sphere_t* sphere = (sphere_t*)obj->priv;
    double base_prime[VECTOR_SIZE] = {0,0,0};

    diff3(sphere->center, base, base_prime);

    double dir_prime[VECTOR_SIZE] = {dir[0], dir[1], dir[2]};
    double a = dot3(dir, dir_prime);
    double b = 2 * dot3(base_prime, dir);
    double temp_base_prime[VECTOR_SIZE] =
                                {base_prime[0], base_prime[1], base_prime[2]};
    double c = dot3(base_prime, temp_base_prime) -
                                             (sphere->radius * sphere->radius);

    double disc = (b*b) - (4*a*c);

    if (disc >= ALMOST_ZERO) {
        dist = ((-1 *b) - sqrt(disc))/(2*a);
        sphere_hitloc(base, dir, dist, obj->hitloc);
    }

    return dist;
}

/**
 * This fuction gets the ambience of the 'sphere' obj.
 *
 * @param obj is the object in question.
 * @param amb is the destination for the ambience information.
 */
void sphere_getamb(obj_t *obj, double* amb) {
    amb[0] = obj->material->ambient[0];
    amb[1] = obj->material->ambient[1];
    amb[2] = obj->material->ambient[2];
#ifdef DBG_SPHERE_GETAMB
    fprintf(stderr, "\namb: (%5.2lf, %5.2lf, %5.2lf)\n",
                    amb[0], amb[1], amb[2]);
#endif
}

/**
 *
 */
static void sphere_hitloc(double* base, double* dir, double dist,
                                                                double* dest) {
    double scalled[3];
    scale3(dist, dir, scalled);
    sum3(base, scalled, dest);
}
#endif
