/**
 * This file defines the functions for a sphere object.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#include "sphere.h"

/** function declarations */
static void sphere_hitloc(double* base, double* dir, double dist,double* dest);
static void sphere_normal(double* hitloc, double* center, double* normal);

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
                        "sphere_init: error while parsing for properties on"
                        " sphere object\n");
        free(sphere);
        free(obj);
        obj = NULL;
        return obj;
    }

    rc += parse_doubles(in, sphere->center, "%lf%lf%lf", VECTOR_SIZE);
    rc += parse_doubles(in, &radius, "%lf", 1);

    if (rc == VECTOR_SIZE + 1) {
        sphere->radius = radius;
        obj->priv = sphere;
        obj->hits = sphere_hits;
        obj->getamb = sphere_getamb;
        obj->getdiff = sphere_getdiff;
        obj->getspec = sphere_getspec;
        obj->obj_dump = sphere_dump;
        obj->free_obj = free_sphere;
    } else {
        fprintf(stderr, "###in sphere.c\n\t"
                        "sphere_init: error while parsing"
                        " sphere object.\n");
        free(sphere);
        free(obj);
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
void sphere_dump(FILE* out, obj_t* obj) {
    sphere_t* asphere = (sphere_t*)obj->priv;

    fprintf(out, "\nDumping object of type Sphere:\n");

    material_dump(out, obj->material);
    /** object specific */
    fprintf(out, "\nSphere data:\n");
    vecprn3(out, "\tcenter - ", asphere->center);
    fprintf(out, "\tradius - \t%3.6lf\n", asphere->radius);
}

/**
 * Checks to see if a ray will his the sphere object.
 *
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

    if (disc > ALMOST_ZERO) {
        dist = ((-1 *b) - sqrt(disc))/(2*a);
        sphere_hitloc(base, dir, dist, obj->hitloc);
        sphere_normal(obj->hitloc, sphere->center, obj->normal);
    }

    return dist;
}

/**
 * This fuction gets the ambience of the 'sphere' obj.
 * @param obj is the object in question.
 * @param amb is the destination for the ambience information.
 */
void sphere_getamb(obj_t *obj, double* amb) {
    amb[0] = obj->material->ambient[0];
    amb[1] = obj->material->ambient[1];
    amb[2] = obj->material->ambient[2];
}

/**
 * This fuction gets the diffuse of the 'sphere' obj.
 * @param obj is the object in question.
 * @param amb is the destination for the diffuse information.
 */
void sphere_getdiff(obj_t *obj, double* diff) {
    diff[0] = obj->material->diffuse[0];
    diff[1] = obj->material->diffuse[1];
    diff[2] = obj->material->diffuse[2];
}

/**
 * This fuction gets the specular of the 'sphere' obj.
 * @param obj is the object in question.
 * @param amb is the destination for the specular information.
 */
void sphere_getspec(obj_t *obj, double* spec) {
    spec[0] = obj->material->specular[0];
    spec[1] = obj->material->specular[1];
    spec[2] = obj->material->specular[2];
}

/**
 * gets the hitlocation of a sphere.
 *
 * @param base base from object
 * @param dir direction
 * @param dist minimum distance.
 * @param dest destination pointer
 */
static void sphere_hitloc(double* base, double* dir, double dist,
                                                                double* dest) {
    double scalled[3];
    scale3(dist, dir, scalled);
    sum3(base, scalled, dest);
}

/**
 * sets a sphere object normal given the hit location and center of the sphere
 * and places it into the destination vector.
 * @param hitloc is a hitlocation.
 * @param center is the center of the sphere.
 * @param dest is where we are to put the normal
 */
static void sphere_normal(double* hitloc, double* center, double* normal) {
    diff3(center, hitloc, normal);
    unitvec(normal, normal);
}

/**
 * frees an object of type sphere
 *
 * @param obj an object of type sphere
 */
void free_sphere(obj_t* obj) {
    sphere_t* sphere = obj->priv;
    free(obj->material);
    free(sphere);
}
