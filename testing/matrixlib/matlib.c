/**
 * File that defines some matrix operations. This library of functions asumes
 * that all matrices are square matrices
 *
 * @author Marco Anton
 */

#include "matlib.h"
/** Forward Declarations */
static void cpy_mat(double* dest, double* src, int size);
static double* mat_init(double* mat, int size);

/**
 * Finds the cross products of two vectors.
 */
void mat_cross(double* v1, double* v2, double* v3, size_t size) {
    double temp_v1[SIZE];
    double temp_v2[SIZE];

    memcpy(temp_v1, v1, size);
    memcpy(temp_v2, v2, size);

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
void mat_print(FILE* out, char* desc, double* matrix, int size) {
    int i, j;
    double mat[size*size];//ummm....?

    cpy_mat(mat, matrix, size);

    fprintf(out, "%s", desc);
    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            fprintf(out, "\t%5.2lf", *(matrix + (i*size)+j));
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
static void cpy_mat(double* dest, double* src, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            *(dest + (i*size)+j) = *(dest + (i*size)+j);
        }
    }
}

/**
 * Initializes matrix with its values to 0.
 * @param mat a matrix to initialize
 * @param size the size of the matrix
 */
static double* mat_init(double* mat, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            *(mat + (i*size)+j) = 0;
        }
    }
    return mat;
}
