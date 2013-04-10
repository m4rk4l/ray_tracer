#ifndef VECLIB_C
#define VECLIB_C

#include "veclib.h"

/** WCK: grade 6/7 */
/** defines the size of vectors to work with. */

/**
 * This file contains basic vector operations.
 * Need better debugging messages.
 *
 * @Author Marco Anton
 * @Version 03/06/2013
 */

/**
 * computes the dot product between two vertices.
 * @param vec1 is a vetcor used to compute the dot product.
 * @param vec2 is another vector used to compute the dot product.
 * @return the dot product of two vertices. -1 if errors happen.
 *
 * need to check that the sizes of the vectors given are the same.
 * some other checks?
 */
double dot3(double* vec1, double* vec2) {
    double ans = 0;
    int i;

    if (vec1 == NULL || vec2 == NULL) {
        fprintf(stderr, "Invalid input. vectors are NULL.\n");
        ans = -1;
    } else {
        for(i = 0; i < SIZE; i++) {
            ans += vec1[i]*vec2[i];
        }
    }

    return ans;
}

/**
 * Scales a vector by a given double.
 * @param scale is a scale number to which to change a vector
 * @param vec_in pointer to a vector to be scaled.
 * @param vec_out pointer to a ''place'' to put the scaled vector.
 *
 * need to check that there is enough space in vec_out to put the vector.
 */
void scale3(double scale, double* vec_in, double* vec_out) {
    int i;

    if(vec_in == NULL || vec_out == NULL) {
        fprintf(stderr, "Invalid input. vectors are NULL.\n");
    } else {
        for(i = 0; i < SIZE; i++) {
            vec_out[i] = vec_in[i]*scale;
        }
    }
}

/**
 * calcultes the length of a vector.
 * @param vec is a pointer to a vector to calculate a length.
 * @return the length for vec, -1 if an error calculating vec.
 */
double length3(double* vec) {
    int i;
    double sqrsum = 0;
    double ans = -1;

    if(vec == NULL) {
        fprintf(stderr, "Invalid input. vector is NULL.\n");
    } else {
        for (i = 0; i < SIZE; i++) {
            sqrsum += vec[i]*vec[i];
        }
        ans = sqrt(sqrsum);
    }

    return ans;
}

/**
 * calculates the difference between two vectors.
 * @param veci_sub pointer to a vector that is going to be substracted from
 *               another one.
 * @param vec_min pointer to a vector that is going to get substracted another
 *               vector
 * @param vec_diff is the difference between vec_min - vec_sub
 */
void diff3(double* vec_sub, double* vec_min, double* vec_diff) {
    int i;

    if(vec_sub == NULL || vec_min == NULL || vec_diff == NULL) {
        fprintf(stderr, "Invalid input. vectors are NULL.\n");
    } else {
        for(i = 0; i < SIZE; i++){
            vec_diff[i] = vec_min[i] - vec_sub[i];
        }
    }
}

/**
 * calculates the sum of two vectors.
 * @param vec_u is a pointer to a vector to add.
 * @param vec_v is a pointer to a vector to add.
 * @param vec_sum is the sum of two vectors.
 *
 * check if there is space for sum in vec_sum
 */
void sum3(double* vec_u, double* vec_v, double* vec_sum) {
    int i;

    if(vec_u == NULL || vec_v == NULL || vec_sum == NULL) {
        fprintf(stderr, "Invalid input. vectors are NULL.\n");
    } else {
        for(i = 0; i < SIZE; i++) {
            vec_sum[i] = vec_u[i] + vec_v[i];
        }
    }
}

/**
 * Function that calculates the unit vector of a given vector.
 * @param v1 a vector whose unit vector we're trying to find.
 * @param v2 place where to save the unit vector.
 *
 * check if there is space for the unit vector in v2
 */
void unitvec(double* v1, double* v2) {
    double l_v1 = length3(v1);
    int i;

    if(v1 == NULL || v2 == NULL) {
        fprintf(stderr, "Invalid input. vectors are NULL.\n");
    } else {
        for(i = 0; i < SIZE; i++) {
            v2[i] = v1[i]/l_v1;
        }
    }
}

/**
 * uses label to put the contents of vec in it for printing.
 * @param label place to hold the contents of vec.
 * @param vec is the vector to printi.
 *
 * need to find a better way to put vector elements into an array.
 // WCK, not sure what you are trying to do here?
 // Why not use printf??
 */
void vecprn3(double* vec) {

    if(vec == NULL) {
        fprintf(stderr, "Invalid input. NULL?.\n");
    } else {
        printf("<%lf, %lf, %lf>\n", vec[0], vec[1], vec[2]);
    }
}

#endif
