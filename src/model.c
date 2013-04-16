#include "model.h"

/** method declarations */
static obj_t* init_specific_object(FILE* in, int obj_type);
static void dump_or_free(FILE* out, list_t* aList, int option);
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
    dump_or_free(out, model->lights, DUMP_OBJ);
    //should dump all elements in model.scene
    dump_or_free(out, model->scene, DUMP_OBJ);
}

/**
 * frees elements from either the lights or the scene models.
 * @param model
 */
void model_free(model_t* model) {
    free_proj(model->proj);
    dump_or_free(NULL, model->lights, FREE_OBJ);
    dump_or_free(NULL, model->scene, FREE_OBJ);
}

/**
 * Funciton that does dumps information or frees objects in a list.
 * @param out is an output stream.
 * @param aList is a list to work with.
 * @param option is an option to be done.
 */
static void dump_or_free(FILE* out, list_t* aList, int option) {
    obj_t* cur = aList->head;
    switch (option) {
        case DUMP_OBJ:
            while(cur != NULL) {
                cur->obj_dump(out, cur);
                cur = cur->next;
            }
            break;
        case FREE_OBJ:
            list_destroy(aList);
            free(aList);
            break;
        default:
            fprintf(stderr, "## in model.c\n\tdump_or_free: invalid option\n");
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
            new_obj = pplane_init(in, obj_type);
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
