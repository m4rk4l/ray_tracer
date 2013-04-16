#ifndef PROJECTION_H
#define PROJECTION_H

#include "Malloc.h"
#include "misc.h"

#define ARGS  3 /** defines the total amount of arguments expected. */

typedef struct projection_type {
    int win_size_pixel[2];    /** Projection screen size in pix */
    double win_size_world[2]; /** Screen size in world coords*/
    double view_point[3];     /** Viewpt Loc in world coords*/
} proj_t;

proj_t* projection_init(int argc, char** argv, FILE* input);
void projection_dump(FILE* out, proj_t* proj);
void map_pix_to_world(proj_t* proj, int x, int y, double* world);
void free_proj(proj_t* proj); 

#endif
