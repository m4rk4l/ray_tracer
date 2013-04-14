#ifndef VECLIB_H
#define VECLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 3

/** vector functions */
double dot3(double* vec1, double* vec2);
void scale3(double scale, double* vecin, double* vecout);
double length3(double* vec);
void diff3(double* vecmin, double* vecsub, double* vecdiff);
void sum3(double* vec1, double* vec2, double* vecsum);
void unitvec(double* vec1, double* vec2);
void vecprn3(double* vec);

/** Matrix functions */
static double IDENT_MAT[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

void mat_cross(double* v1, double* v2, double* v3, size_t size);
void mat_mul(double* x, double* y, double* z, size_t size);
void mat_xpose(double* x, double* z, size_t size);
void mat_xform(double* y, double* x, double* z, size_t size);
void mat_proj(double* n, double* v, double* w, size_t size);
void mat_print(FILE* out, char* desc, double* matrix, int size);
#endif
