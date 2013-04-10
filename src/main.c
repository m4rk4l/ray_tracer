/**
 * This file defines the main function for the 
 * project that acts as a driver.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#ifndef MAIN_C
#define MAIN_C

#include "model.h"
#include "image.h"

/**
 * entry point for an implementation of raytracer.
 *
 * @param argc argument counter.
 * @param argv array conataining values of the arguments
 */
int main(int argc, char** argv) {
    
    model_t* model = (model_t*)Malloc(sizeof(model_t));
    int rc;

    model->proj = projection_init(argc, argv, stdin);

    projection_dump(stderr, model->proj);

    model->lights = list_init();
    model->scene = list_init();

    rc = model_init(stdin, model);
    model_dump(stderr, model);

fprintf(stderr, "main.c - rc: %d\n", rc);
    if (rc == 0) {
        make_image(model);
    }

    list_destroy(model->lights);
    list_destroy(model->scene);
    free(model->proj);
    free(model);

    return (EXIT_SUCCESS);
}
#endif
