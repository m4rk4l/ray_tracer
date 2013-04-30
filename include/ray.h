#ifndef RAY_H
#define RAY_H


#include "model.h"
#include "object.h"
#include "veclib.h"
#include "illuminate.h"

void ray_trace(model_t* model, double* base, double* dir, double* intensity,
                                        double total_dist, obj_t* last_hit);

obj_t* find_closest_obj(list_t* objs, double* base, double* dir, void* smt,
                                                int modify, double* mindist);
#endif
