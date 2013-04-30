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
 * @return 0 if diffuse could be applied or 1 if not.
 */
int process_light(list_t* lst, obj_t* hitobj, obj_t* lobj, double* ivec) {
    int ans = 0;
    double diffuse[VECTOR_SIZE];
    double dir_light[3];
    double dir_obj[3];
    double dist_obj;
    double dist_light;
    double cos_theta;

    light_t* light = lobj->priv;
    diff3(hitobj->hitloc, light->center, dir_light);

    if (dot3(dir_light, hitobj->normal) < 0) {
#ifdef DBG_DIFFUSE
    fprintf(stderr, "selfocluding object.\n");
#endif
        ans = 1;
        return ans;
    }

    int mod = 1; //set modify flag to false.
    obj_t* closest = find_closest_obj(lst, hitobj->hitloc, dir_light,
                                                   NULL, mod, &dist_obj);
    dist_light = length3(dir_light);

    if (closest != NULL && closest->objid != hitobj->objid &&
                                                dist_obj < dist_light) {
#ifdef DBG_DIFFUSE
    /** If occluded by another object */
    fprintf(stderr, "hit object occluded by :\t%d\n", hitobj->objid);
    fprintf(stderr, "distance was           :\t%lf\n", dist_obj);
#endif
        ans = 1;
        return ans;
    }

    unitvec(hitobj->normal, dir_obj);
    unitvec(dir_light, dir_light);
    cos_theta = dot3(dir_obj, dir_light);
    hitobj->getdiff(hitobj, diffuse);

#ifdef DBG_DIFFUSE
    fprintf(stderr, "hit object id was       :\t%d\n", hitobj->objid);
    fprintf(stderr, "hit object type was     :\t%d\n", hitobj->objtype);
    vecprn3(stderr, "hit point was           : ", hitobj->hitloc);
    vecprn3(stderr, "normal at hitpoint      : ", hitobj->normal);
    fprintf(stderr, "light object id         :\t%d\n", lobj->objid);
    vecprn3(stderr, "light center was        : ", light->center);
    vecprn3(stderr, "unit vector to light is : ", dir_light);
    fprintf(stderr, "distance to light is    :\t%5.3lf\n", dist_light);
    fprintf(stderr, "cosine is               :\t%5.3lf\n", cos_theta);
#endif

    ivec[0] += diffuse[0] * lobj->emissivity[0] * cos_theta / dist_light;
    ivec[1] += diffuse[1] * lobj->emissivity[1] * cos_theta / dist_light;
    ivec[2] += diffuse[2] * lobj->emissivity[2] * cos_theta / dist_light;

#ifdef DBG_DIFFUSE
    vecprn3(stderr, "Emissivity of the light ", lobj->emissivity);
    vecprn3(stderr, "Diffuse reflectivity    ", diffuse);
    vecprn3(stderr, "Current ivec            ", ivec);
#endif

    return ans;
}
