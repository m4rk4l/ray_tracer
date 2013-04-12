/**
 * File that defines some matrix operations.
 *
 * @author Marco Anton
 */

#include "matlib.h"

/**
 *
 */
void mat_cross(double* v1, double* v2, double* vr3, size_t size) {
}

/**
 *
 */
void mat_mul(double** x, double** y, double** z, size_t size) {
}

/**
 *
 */
void mat_xpose(double** x, double** z, size_t size) {
}

/**
 *
 */
void mat_xform(double** y, double* x, double* z, size_t size) {
}

/**
 *
 */
void mat_proj(double* n, double* v, double* w, size_t size) {
}

/**
 * prints an object with a description.
 * @param desc is a description of this matrix
 * @param m is a matrix to print
 */
void mat_print(FILE* out, char* desc, double** m, size_t size) {
    int i, j;
    double mat[][size] = m;

    fprintf(out, "%s ()", desc);
    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            fprintf(out,"%5.2lf" mat[i][j]);
        }
    }
}
