#include "illuminate.h"

/**
 * file that contains the logic necesary to compute lights.
 * @author Marco Anton
 * @author Ben Dana
 */

/**
 * diffuse_illumination front end for the diffuse computation.
 * @param model pointer to the model structure.
 * @param hitobj object that was hit by the ray.
 * @param intensity where to add the intensity.
 */
void diffuse_illumination(model_t* model, obj_t* hitobj, double* intensity) {
    obj_t* cur_light = model->lights->head;
    while(cur_light != NULL) {
        process_light(model->scene, hitobj, cur_light, intensity);
        cur_light = cur_light->next;
    }
}

/**
 * process the light at certain hitlocation of an object.
 * @param lst list of all objects.
 * @param hitobj the object hit by the ray.
 * @param lobj the current light source
 * @param ivec intensity vector.
 * @return ...
 */
int process_light(list_t* lst, obj_t* hitobj, obj_t* lobj, double* ivec) {
    int ans = -1;
    double dir[3];
    light_t* light = lobj->priv;
    diff3(light->center, hitobj->hitloc, dir);
    //if (0 > dot3(dir, obj->normal)) {
    //}
    return ans;
    //if hitobj occludes itself
    //  return
    //find_closest_object() along a ray from hitloc to the center of the light
    //if one exist and is closer than the light // the light is occluded by obj
    //  return
    //compute the illumination and add it to *pix
}
