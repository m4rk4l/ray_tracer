/**
 * This file defines the functions that all objects share
 * and creates a form of polymorphism.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#ifndef OBJECT_C
#define OBJECT_C

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

    obj->objtype = objtype;
    obj->objid = id++;

    if (!(FIRST_TYPE <= objtype && objtype <= LAST_LIGHT)) {// not a light.
        obj->material = (material_t*)Malloc(sizeof(material_t));
        int rc = material_init(in, obj->material); //parse for material info
        if (rc != 0) {
            fprintf(stderr, "### in object.c\n\t"
                            "error while parsing for material\n");
            free(obj->material);
            free(obj);
            obj = NULL;
        }
    }

    return obj;
}

#endif
