#include "ray.h"

/**
 * traces a single ray and returns the composite intensity of the light it
 * encounters. Start of the ray cannot be assumed to be the viewpt.
 * @param model is a pointer to the model container.
 * @param base is the location of the viewer or previous hit.
 * @param dir is a unit vector in the directio of object.
 * @param intensity is the return location.
 * @param total_dist total distance the ray has traveled so far.
 * @param last_hit obj that reflected this ray or NULL.
 */
void ray_trace(model_t* model, double* base, double* dir, double* intensity,
                                        double total_dist, obj_t* last_hit) {
    double mindist;
    obj_t* closest = find_closest_obj(model->scene, base, dir, NULL, &mindist);

    if (closest == NULL) {
        return;
    }
#ifdef DBG_HIT
    fprintf(stderr, " HIT %4d: %5.1lf (%5.1lf, %5.1lf, %5.1lf) - ",
                           closest->objid, mindist, closest->hitloc[0],
                           closest->hitloc[1], closest->hitloc[2]);
#endif
    //add mindist to total_dist
    total_dist += mindist;
    //set intensity to the ambient reflectivity of closest
    closest->getamb(closest, intensity);
    //TODO: add diffuse reflectivity of the object ath the hitpoint to the
    //intensity vector.
    diffuse_illumination(model, closest, intensity);
    //divide intensity by total_dist
    double factor = 1/total_dist;
    double temp_intensity[3] = {intensity[0], intensity[1], intensity[2]};
    scale3(factor, temp_intensity, intensity);
#ifdef DBG_AMB
    fprintf(stderr, " AMB (%5.1lf, %5.1lf, %5.1lf) - ",
                            intensity[0], intensity[1], intensity[2]);
#endif
}

/**
 * finds the colsest object to an object.
 * @param objs
 * @param base
 * @param dir
 * @param smt
 * @param mindist
 */
obj_t* find_closest_obj(list_t* objs, double* base, double* dir, void* smt,
                                                            double* mindist) {
    obj_t* closest = NULL;
    obj_t* cur_obj = objs->head;
    double shortest = -1;
    while(cur_obj != NULL) {
        double dist = cur_obj->hits(base, dir, cur_obj);
#ifdef DBG_FND
        fprintf(stderr, " FND %4d: %5.1lf - ", cur_obj->objid, dist);
#endif
        if((dist < shortest || shortest == -1) && dist != -1) {
            closest = cur_obj;
            shortest = dist;
        }
        cur_obj = cur_obj->next;
    }
    *mindist = shortest;
    return closest;
}
