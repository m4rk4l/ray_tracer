/**
 * File that defines some matrix operations.
 *
 * @author Marco Anton
 */

#include "matlib.h"
/** Forward Declarations */
static void cpy_mat(double* dest, double* src, size_t size);

/**
 *
 */
void mat_cross(double* v1, double* v2, double* vr3, size_t size) {
}

/**
 *
 */
void mat_mul(double* x, double* y, double* z, size_t size) {
}

/**
 *
 */
void mat_xpose(double* x, double* z, size_t size) {
}

/**
 *
 */
void mat_xform(double* y, double* x, double* z, size_t size) {
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
void mat_print(FILE* out, char* desc, double* matrix, size_t size) {
    unsigned int i, j;
    double* mat = { {0,0,0}, {0,0,0}, {0,0,0}};

    cpy_mat(mat, matrix, size);

    fprintf(out, "%s", desc);
    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            fprintf(out, "\t%5.2lf", mat[i][j]);
        }
        fprintf(out, "\n");
    }
}

/**
 * copies the elements of a matrix into another one.
 * @param dest is a pointer to put the result.
 * @param src is a pointer that holds what we are trying to copy.
 * @param size is the size of our matrix we are assuming a square matrix
 *             in other words, its a size x size matrix.
 */
static void cpy_mat(double* dest, double* src, size_t size) {
    unsigned int i, j;
    for (i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            dest[i][j] = src[i][j];
        }
    }
}
