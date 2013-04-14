#ifndef MATERIAL_H
#define MATERIAL_H

#include "misc.h"

typedef struct material_type {
    double ambient[VECTOR_SIZE];
    double diffuse[VECTOR_SIZE];
    double specular[VECTOR_SIZE];
} material_t;


int material_init(FILE* in, material_t* mat);
void material_dump(FILE* out, material_t* material);


#endif
