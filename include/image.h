#ifndef IMAGE_H
#define IMAGE_H

#include "model.h"
#include "projection.h"
#include "ray.h"

void make_image(model_t* model);
void make_pixel(model_t* model, int x, int y, unsigned char* pixval);
#endif
