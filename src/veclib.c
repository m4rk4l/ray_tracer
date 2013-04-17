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
        double u[SIZE];
        double v[SIZE];
        cpy_vec(u, vec1, SIZE);
        cpy_vec(v, vec2, SIZE);

        for(i = 0; i < SIZE; i++) {
            ans += u[i]*v[i];
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
        double v[SIZE];
        cpy_vec(v, vec_in, SIZE);
        for(i = 0; i < SIZE; i++) {
            vec_out[i] = v[i]*scale;
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
        double u[SIZE];
        double v[SIZE];
        cpy_vec(u, vec_sub, SIZE);
        cpy_vec(v, vec_min, SIZE);
        for(i = 0; i < SIZE; i++){
            vec_diff[i] = v[i] - u[i];
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
        double u[SIZE];
        double v[SIZE];
        cpy_vec(u, vec_u, SIZE);
        cpy_vec(v, vec_v, SIZE);
        for(i = 0; i < SIZE; i++) {
            vec_sum[i] = u[i] + v[i];
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

    if(v1 == NULL || v2 == NULL) {
        fprintf(stderr, "Invalid input. vectors are NULL.\n");
    } else {
        double v[SIZE];
        cpy_vec(v, v1, SIZE);
        double l_v = length3(v);
        int i;
        for(i = 0; i < SIZE; i++) {
            v2[i] = v[i]/l_v;
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
void vecprn3(FILE* out, char* desc, double* vec) {

    if(vec == NULL) {
        fprintf(out, "Invalid input. NULL?.\n");
    } else {
        fprintf(out, "%s\t<%5.2lf, %5.2lf, %5.2lf>\n", desc, vec[0], vec[1],
                                                                    vec[2]);
    }
}

/** ########################## MATRICES FUNCTIONS ########################## */
/**
 * File that defines some matrix operations. This library of functions asumes
 * that all matrices are square matrices
 *
 * @author Marco Anton
 */

/** Forward Declarations */
static void multiply(int rowA, int colA, int rowB, int colB, double* A,
                                               double* B, double* product);

/**
 * Finds the cross products of two vectors.
 * @param v1 pointer to a vector.
 * @param v2 pointer to a vector.
 * @param v3 pointer to a vector where one is to put reslult of cross product.
 * @param size_t is a size of the vectors.
 */
void mat_cross(double* v1, double* v2, double* v3, size_t size) {
    double u[size];
    double w[size];

    cpy_vec(u, v1, size);
    cpy_vec(w, v2, size);

    v3[0] = (u[1]*w[2]) - (u[2]*w[1]);
    v3[1] = (u[2]*w[0]) - (u[0]*w[2]);
    v3[2] = (u[0]*w[1]) - (u[1]*w[0]);
}

/**
 * multiplies two matrices. This assumes that the matrices are squares.
 * See top comment.
 * @param x is a pointer to a matrix
 * @param y is a pointer to a matrix
 * @param z is a pointer where to put the answer.
 * @size is the size of the array.
 */
void mat_mul(double* x, double* y, double* z, size_t size) {
    double A[size*size];
    double B[size*size];

    cpy_mat(A, x, size);
    cpy_mat(B, y, size);

//fprintf(stderr, "Matrix Multiplication\n");
//mat_print(stderr, "A: ", A, size);
//mat_print(stderr, "B: ", B, size);

    multiply(size, size, size, size, A, B, z);
//mat_print(stderr, "z: ", z, size);
}

/**
 * Multiplies a matrix by a vector.
 * @param x is a matrix
 * @param y is a vector
 * @param is a vector product of Xy
 * @param size is the size of the square matrix X and size of a vector y.
 */
void mat_vec_mul(double* x, double* y, double* z, size_t size) {
    double A[size*size];
    double v[size];

    cpy_mat(A, x, size);
    cpy_vec(v, y, size);

//fprintf(stderr, "Matrix vector multiplication\n");
//mat_print(stderr, "A: ", A, size);
//vecprn3(stderr, "v: ", v);

    multiply(size, size, size, 1, A, v, z);
}

/**
 * Function that given the number of rows and columns of two matrices
 * yields the product of them.
 * @param rowA number of rows of A
 * @param colA number of cols of A
 * @param rowB number of rows of B
 * @param colB number of cols of B
 * @param A an array.
 * @param B an array.
 *
 * Note that this function assumes correct input!!
 */
static void multiply(int rowA, int colA, int rowB, int colB, double* A,
                                               double* B, double* product) {
    int i, j, k;
//    int count = 1;
    double sum = 0;
//fprintf(stderr, "-----%d %d %d %d----\n", rowA, colA, rowB, colB);
    for (i = 0; i < rowA; i++) {
        for (j = 0; j < colB; j++) {
            fprintf(stderr, "%d\n", j);
            for (k = 0; k < colA; k++) {
                sum += *(A + ((i*rowA)+ k)) * *(B + ((k*colB) + j));
//fprintf(stderr, "%d (A_%d%d * v_%d%d): %5.2lf * %5.2lf = %5.2lf\n",
//count++, i, k, k, j, *(A + ((i*rowA)+ k)), *(B + ((k*colB) + j)), sum);
            }
            if (rowA == 1 || colA == 1 || rowB == 1 || colB == 1) {
                product[i] = sum;
//fprintf(stderr, "prod %d: %5.2lf\n", i, product[i]);
            } else {
                *(product + ((i*rowA) + j)) = sum;
//fprintf(stderr, "prod %d, %d: %5.2lf\n", i, j, *(product + ((i*rowA) + j)));
            }
            sum = 0;
        }
    }
}

/**
 * Transposes a matrix
 * 
 * @param x is a matrix to transpose.
 * @param z is a pointer to put our transposed matrix.
 * @param size size of the square matrix.
 */
void mat_xpose(double* x, double* z, size_t size) {
    double A[size*size];
    unsigned int i, j;

    cpy_mat(A, x, size);

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            z[(j*size)+i] = A[(i*size)+j];
        }
    }

}

/**
 * Perform a linear transform in four dimensional space
 *
 * by applying a 3x3 matrix to a 3x1 column vector
 * @param y transoform matrix
 * @param x input vector
 * @param output vector
 */
void mat_xform(double* y, double* x, double* z, size_t size) {
    mat_vec_mul(y, x, z, size);
}

/**
 * project a vector onto a plane.
 *
 * @param n plane normal.
 * @param v input vector.
 * @param w projected vector.
 */
void mat_proj(double* n, double* v, double* w, size_t size) {
    double vec[size];
    scale3(dot3(n, v), n, vec);
    diff3(vec, v, w);
}

/**
 * prints an object with a description.
 *
 * @param out is an output stream.
 * @param desc is a description of this matrix
 * @param m is a matrix to print
 * @param size of the square matrix
 */
void mat_print(FILE* out, char* desc, double* matrix, int size) {
    int i, j;
    double mat[size*size];//ummm....?

    cpy_mat(mat, matrix, size);// could have used memcpy?

    fprintf(out, "%s", desc);
    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            fprintf(out, "\t%5.2lf", *(mat + (i*size)+j));
        }
        fprintf(out, "\n");
    }
}

/** Note that for the following two functions the dest and src params MUST
 * be pointing to different elements */

/**
 * copies the elements of a matrix into another one.
 * @param dest is a pointer to put the result.
 * @param src is a pointer that holds what we are trying to copy.
 * @param size is the size of our matrix we are assuming a square matrix
 *             in other words, its a size x size matrix.
 */
void cpy_mat(double* dest, double* src, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            dest[(i*size)+j] = src[(i*size)+j];
            //*(dest + (i*size)+j) = *(dest + (i*size)+j);
        }
    }
}

/**
 * copies elements of a vector into another one.
 * @param dest is apointer to put the result
 * @param src is a pointer to the source vector.
 * @param size is the size of the vector.
 */
void cpy_vec(double* dest, double* src, int size) {
    int i;
    for (i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}
