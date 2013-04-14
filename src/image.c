/**
 * This file defines the functiobs for the entire image.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#ifndef IMAGE_C
#define IMAGE_C

#include "image.h"

/** Funciton declarations */ 
static void ppm_header(FILE* out, int width, int height);
static void get_dir(double* view, double* world, double* dir);
static void clamp_intensity(double min, double max, double* intensity);

/**
 * generates a ppm file
 */
void make_image(model_t* model) {
    unsigned char* pixmap = NULL;
    int width = model->proj->win_size_pixel[0];
    int height = model->proj->win_size_pixel[1];
    int x, y;
    int pixmap_size = VECTOR_SIZE * width * height * sizeof(unsigned char);

    // compute size of output image and malloc pixmap.
    pixmap = Malloc(pixmap_size);
    int incrementer = 0;
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
#ifdef DBG_PIX
    //fprintf(stderr, "\nx, y -  %d %d\n", x, y);
    //fprintf(stderr, "\nstart end -  %d %d\n", (width - x), (height - y));
    fprintf(stderr, "\nPIX %4d %4d - ", x, y);
#endif
            make_pixel(model, x, height - y, (pixmap + incrementer));
            incrementer += VECTOR_SIZE; // c will do array arithmatic above
        }
    }

    ppm_header(stdout, width, height);
    fwrite(pixmap, pixmap_size, 1, stdout);
    free(pixmap);
}

/**
 * Derives the rgb components of a single vector.
 * @param model pointer to a model definition.
 * @param x is location on the x axis
 * @param y is a location on the y axis
 * @param pixval is a pointer to a pixel we're trying to update. 
 */
void make_pixel(model_t* model, int x, int y, unsigned char* pixval) {
    double dir[VECTOR_SIZE];
    double world[VECTOR_SIZE];
    double intensity[VECTOR_SIZE];

    map_pix_to_world(model->proj, x, y, world);
#ifdef DBG_WORLD
    fprintf(stderr, " WRL (%5.1lf, %5.1lf) - ", world[0], world[1]);
#endif
    int i;
    for (i = 0; i < VECTOR_SIZE; i++) {
        intensity[i] = 0.0;
    }

    get_dir(model->proj->view_point, world, dir);
#ifdef DBG_MAKE_PIXEL
    fprintf(stderr, "\ndirection: (%5.2lf, %5.2lf, %5.2lf)\n",
                    dir[0], dir[1], dir[2]);
#endif
    ray_trace(model, model->proj->view_point, dir, intensity, 0.0, NULL);
    //clamp each element of intensity to the range (0.0, 1.0)
    clamp_intensity(SCALE_RGB_MIN, SCALE_RGB_MAX, intensity);
    //set rgb components of vector pointed to pixval to 255 * its intensity.
    for (i = 0; i < VECTOR_SIZE; i++) {
        pixval[i] = intensity[i] * SCALE_RGB;
    }
}

/**
 * finds the unit vector from view point to world.
 * @param viewpoint a pointer to a viewpoint vector.
 * @param world a ponter to a world vector.
 * @param dir a place to put the unit vector.
 * vector = W-V. then must find unit vec of this vector.
 */
static void get_dir(double* view_point, double* world, double* dir) {
    double vec[3] = {0.0, 0.0, 0.0};
    diff3(view_point, world, vec);
    unitvec(vec, dir);
}

/**
 * sets the values of intensity to be at least min or at most max.
 * @param min is the minimum value of an intensity index.
 * @param max is the maximum value of an intensity index.
 * @param intensity is a pointer to an array containing values of intensity 
 */
static void clamp_intensity(double min, double max, double* intensity) {
    int i;
    for (i = 0; i < VECTOR_SIZE; i++) {
        if(*(intensity + i) < min) {
            *(intensity + i) = min;
        } else if (*(intensity + i) > max) {
            *(intensity + i) = max;
        }
    }
#ifdef DBG_CLAMP_INTENSITY
    fprintf(stderr, "\nclamped intensity: (%5.2lf, %5.2lf, %5.2lf)\n",
                    intensity[0], intensity[1], intensity[2]);
#endif
}

/**
 * writes a ppm file to a file.
 */
static void ppm_header(FILE* out, int width, int height) {
    fprintf(out, "P6 %d %d %d\n", width, height, SCALE_RGB);
}

#endif
