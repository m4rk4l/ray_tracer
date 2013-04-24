#include "light.h"
#include "veclib.h"
#include "model.h"
#include "list.h"

/**
 * Initiates a light object.
 * @param in an input stream
 * @param objtype is the type of the object. Must be a light
 */
obj_t* light_init(FILE* in, int objtype) {
    obj_t* light_obj = object_init(in, objtype);
    if (light_obj == NULL) {
        fprintf(stdout, "### in light.c\n\t"
                        "error while creating an object.\n");
        return light_obj;
    }

    light_t* light = Malloc(sizeof(light_t));
    int error = parse_doubles(in, light->center, "%lf%lf%lf", VECTOR_SIZE);
    
    if (error != 0) {
        fprintf(stderr, "### in light_init:\n\t"
                        "erorr while parsing for light location.\n");
        free(light);
        free(light_obj);
        light_obj = NULL;
    } else {
        light_obj->priv = light;
        light_obj->obj_dump = light_dump;
        light_obj->free_obj = free_light;
    }


    return light_obj;
}

/**
 * Dumps a light object.
 * @param out is an output stream
 * @param obj is the light object we are trying to dump.
 */
void light_dump(FILE* out, obj_t* obj) {
    light_t* light = (light_t*)obj->priv;

    fprintf(out, "\nDumping object of type Light\n");
    vecprn3(out, "\temisivity - ", obj->emissivity);
    vecprn3(out, "\tlocation - ", light->center);
}

/**
 * Function that frees all the memory allocations due to a light.
 * @param obj is the light we are trying to free.
 */
void free_light(obj_t* obj) {
    light_t* light = obj->priv;
    free(light);
}
