/**
 * This file defines the functions that all objects share
 * and creates a form of polymorphism.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#include "object.h"

/** Some function definitions */

/**
 * Initialices an object.
 * 
 * @param in, input from standard in.
 * @param objtype, the int value for the type of object.
 * @return obj, the newly created object.
 */
obj_t* object_init(FILE* in, int objtype) {
    static int id = 0;
    obj_t* obj = Malloc(sizeof(obj_t));
    obj->next = NULL;
    obj->priv = NULL;
    int rc = 0;

    obj->objtype = objtype;
    obj->objid = id++;

    if (FIRST_TYPE <= objtype && objtype <= LAST_TYPE) {// not a light.
        obj->material = (material_t*)Malloc(sizeof(material_t));
        rc = material_init(in, obj->material); //parse for material info
        if (rc != VECTOR_SIZE * VECTOR_SIZE) {
            fprintf(stderr, "### in object.c\n\t"
                            "object_init: error while parsing for material\n");
            free(obj->material);
            free(obj);
            obj = NULL;
        } else {// maybe set all elements of the object to null...
            obj->next = NULL;
            obj->priv = NULL;
        }

    } else if (FIRST_LIGHT <= objtype && objtype <= LAST_LIGHT) {// light
        rc = parse_doubles(in, obj->emissivity, "%lf%lf%lf", VECTOR_SIZE);
        if (rc != VECTOR_SIZE) {
            fprintf(stderr, "### in object.c\n\t"
                            "object_init: error while parsing for"
                            " emisivity.\n");
            free(obj);
            obj = NULL;
        } else {
            obj->next = NULL;
            obj->material = NULL;
            obj->priv = NULL;
        }
    } else {
        fprintf(stderr, "### in object.c\n\tobject_init:"
                        " invalid object id.\n");
    }

    return obj;
}
