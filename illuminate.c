#include "light.h"
#include "veclib.h"
#include "model.h"
#include "list.h"
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
    //distance from A to B = 
    //diff3(A, B,minDisToObj)
    //MinDisDouble = length(minDisToObj)
    double minDisDoubleLight; // variable that holds distance length
    double *minDisLight; //vector that holds distance vector from obj to light
    diff3(hitobj, lobj, minDisLight); // calculates difference between main obj and light
    minDisDoubleLight = length3(minDisLight); // returns distance between main obj and light
    diff3(lobj->priv->center, hitobj->hitloc, direction) // calculates direction of obj 
    if (0.0 > dot3(direction, obj->normal)) { // check for self-occlusion
        return 0;
    } else {
        void *stub;
        obj_t *closest_object = find_closest_obj(lst, hitobj->hitloc, direction,
            stub, minDisToObj); // exlude hitobj form lst somehow? shouldn't be 
                                // checking if select object is in way of same object
        if (NULL == *closest_object) { // No object is blocking light source
            // right now, closest_object might return same object that we are checking occlusion on
            //TODO: compute the illumination and add to *pix
            return 1;
        } else {
          double minDisDoubleObj; // variable that holds distance length of closest_object
          double *minDisObj; //vector that holds distance vector from closest_object to main object
          diff3(hitobj, min, minDisObj); // calculates difference between main obj and obj
          minDisDouble = length3(minDisObj); // returns distance between main obj and obj
          if (minDisObj < minDisLight) { // if true, object is closer than light to main obj
              return 0;
          } else {
            // have access to the distance and the object itself
            //TODO: compute the illumination and add to *pix
            return 0;
          }
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
