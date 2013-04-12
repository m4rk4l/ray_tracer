#ifndef MATLIB_H
#define MATLIB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//need to delete size and replace in veclib
#define SIZE 3

static double IDENT_MAT[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

void mat_cross(double* v1, double* v2, double* v3, size_t size);
void mat_mul(double* x, double* y, double* z, size_t size);
void mat_xpose(double* x, double* z, size_t size);
void mat_xform(double* y, double* x, double* z, size_t size);
void mat_proj(double* n, double* v, double* w, size_t size);
void mat_print(FILE* out, char* desc, double* matrix, int size);

#endif
