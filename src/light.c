#include "light.h"
#include "veclib.h"
#include "model.h"
#include "list.h"

int light_init() {
}
 /*
 * diffuse_illumination – Comment me
 * Parameters: model - pointer to the model structure
 * hitobj – object that was hit by the ray
 * intensity – where to add the intensity
 */
void diffuse_illumination(model_t *model, obj_t *hitobj,
 double *intensity){
    //for all lights on the light list { 
    //BD: Need access for all objects and lights, get from model.
    //    process_light()
    //}
    obj_t *current = model->lights->head;
    while (current->next != null) {
        process_light(model->scene, hitobj, current);
        current = current->next;
    } //current is now pointing to tail
    process_light(model->scene, hitobj, current);
}
/*
 * process_light – Comment me
 * Parameters lst – list of all objects
 * hitobj – The object hit by the ray
 * lobj - The current light source
 * ivec – [r, g, b] intensity vector
 * Return: 0 if occluded, 1 if light hits object, -1 if error.
 */
int process_light(list_t *lst, obj_t *hitobj, obj_t *lobj, 
 double *ivec) {
    double *direction = {0.0, 0.0, 0.0};
    double *minDistance;
    diff3(lobj->priv->center, hitobj->hitloc, direction)
    if (0.0 > dot3(direction, obj->normal)) { // check for self-occlusion
        return 0;
    } else {
        void *stub;
        obj_t *closest_object = find_closest_obj(lst, hitobj->hitloc, direction,
            stub, minDistance);
        if (NULL == *closest_object) { // No object is blocking light source
            return 1;
        } else {
            // have access to the distance and the object itself
            return 0;
        }
    }
    /*if the hitobj occludes itself 
        return
    find_closest_object() along a ray from hitloc to the center of the light
    if one exists and is closer than the light // the light is occluded by the object
    return
compute the illumination and add it to *pix;
*/
}