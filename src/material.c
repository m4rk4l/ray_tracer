/**
 * This file defines the functions necessary to initialize 
 * the material structs.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#ifndef MATERIAL_C
#define MATERIAL_C

#include "material.h"

/**
 * This Function initializes the material struct with 
 * the parameters passed.
 *
 * @param in, is standard input.
 * @param mat, is the material object to be initialized.
 */
int material_init(FILE* in, material_t* mat) {
    int rc = 0;
    rc += parse_doubles(in, mat->ambient, "%lf%lf%lf", VECTOR_SIZE);
    rc += parse_doubles(in, mat->diffuse, "%lf%lf%lf", VECTOR_SIZE);
    rc += parse_doubles(in, mat->specular, "%lf%lf%lf", VECTOR_SIZE);
    return rc;
}

/**
 * This function dumps out any errors to the apropos file.
 * 
 * @param out, is the output stream which should be standard error.
 * @param material, is the object to have it's info dumped.
 */
void material_dump(FILE* out, material_t* material) {
    fprintf(out, "Material data:\n"
                "\tAmbient -\t%6.3lf\t%6.3lf\t%6.3lf\n"
                "\tDiffuse -\t%6.3lf\t%6.3lf\t%6.3lf\n"
                "\tSpecular -\t%6.3lf\t%6.3lf\t%6.3lf\n",
    material->ambient[0], material->ambient[1], material->ambient[2],
    material->diffuse[0], material->diffuse[1], material->diffuse[2],
    material->specular[0], material->specular[1], material->specular[2]);
}


#endif
