#ifndef MODEL_C
#define MODEL_C

#include "model.h"

/** method declarations */
static obj_t* init_specific_object(FILE* in, int obj_type);
static void dump_objects(FILE* out, list_t* aList);
static void obj_dump(FILE* out, obj_t* obj);

/**
 * initializes the objects in a model. This funciton should parse and create
 * new object_types according to input.
 */
int model_init(FILE* in, model_t* model) {
    int rc = 0;
    int objtype;
    obj_t* newobj = NULL;

    while(rc != -2) { //do while you havent reached the end of file
        rc = parse_doubles(in, NULL, "", 0);// parse for nothing. check misc.c
        rc = parse_ints(in, &objtype, "%d", 1); //parses one element the obj

        // if there is an error while parsing the objtype, break out of loop
        if (rc == -1) {
            fprintf(stdout, "### In model.c\n\tmodel_init: error reading"
                            " object type.\n");
            break;
        } else if (rc == -2) {
            fprintf(stderr, "### REACHED THE END OF FILE ###\n");
            break;
        }

        newobj = init_specific_object(in, objtype);

        // check if newobj != null, if so parsing obj error.
        if (newobj == NULL) {
            fprintf(stderr, "### in model.c\n\tmodel_init: "
                            "error while parsing object.\n");
            rc++;
            break;
        }

        // otherwise, add it to a list depending on the objtype
        if (FIRST_TYPE <= objtype && objtype <= LAST_LIGHT) { // light
            list_add(model->lights, newobj);
        } else { // scene
            list_add(model->scene, newobj);
        }
    }

    if(rc == -2) { // reached the end of file without errors.
        rc = 0;
    }

    return rc;
}

/**
 *
 */
void model_dump(FILE* out, model_t* model) {
    //should dump all elements in model.lights
    dump_objects(out, model->lights);
    //should dump all elements in model.scene
    dump_objects(out, model->scene);
}

/**
 * Dump out information for each obj.
 */
static void dump_objects(FILE* out, list_t* aList) {
    obj_t* cur = aList->head;
    while(cur != NULL) {
        obj_dump(out, cur);
        cur = cur->next;
    }
}

/**
 * big switch statement for initializing objects in specific.
 * @param in is a file to parse for data about an object.
 * @param new_obj a newly created object to add to a list.
 * @return if errors occur should return a number > 0.
 */
static obj_t* init_specific_object(FILE* in, int obj_type) {
    obj_t* new_obj = NULL;
    switch(obj_type) {
        case LIGHT:
        break;
        case SPOTLIGHT:
        break;
        case PROJECTOR:
        break;
        case SPHERE:
            new_obj = sphere_init(in, obj_type);
        break;
        case PLANE:
            new_obj = plane_init(in, obj_type);
        break;
        case FINITE_PLANE:
        break;
        case TILED_PLANE:
        break;
        case TEX_PLANE:
        break;
        case REF_SPHERE:
        break;
        case P_SPHERE:
        break;
        case P_PLANE:
        break;
        case PARABOLOID:
        break;
        case CYLINDER:
        break;
        case CONE:
        break;
        case HYPERBOLOID:
        break;
        default:
            fprintf(stderr, "#### in model.c\n\tinit_object: obj_type not"
                            " defined\n");
    }
    return new_obj;
}

/**
 * Dumps information related to an object to standard error.
 *
 * @param out is a file to write to.
 * @param obj is the obj that we need info from.
 */
static void obj_dump(FILE* out, obj_t* obj) {
    int type = obj->objtype;
    switch(type) {
        case LIGHT:
        break;
        case SPOTLIGHT:
        break;
        case PROJECTOR:
        break;
        case SPHERE:
            sphere_dump(out, obj);
        break;
        case PLANE:
            plane_dump(out, obj);
        break;
        case FINITE_PLANE:
        break;
        case TILED_PLANE:
        break;
        case TEX_PLANE:
        break;
        case REF_SPHERE:
        break;
        case P_SPHERE:
        break;
        case P_PLANE:
        break;
        case PARABOLOID:
        break;
        case CYLINDER:
        break;
        case CONE:
        break;
        case HYPERBOLOID:
        break;
        default:
            fprintf(out, "invalid objtype: %d\n", type);
    }
}
#endif
