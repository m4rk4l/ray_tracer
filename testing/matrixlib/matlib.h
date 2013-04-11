#ifndef MATLIB_H
#define MATLIB_H

#include <stdlib.h>
#include <stdio.h>

#define IDENT_MAT {(1, 0, 0), (0, 1, 0), (0, 0, 1)}

void mat_cross(double* v1, double* v2, double* v3);
void mat_mul(double** x, double** y, double** z);
void mat_xpose(double** x, double** z);
void mat_xform(double** y, double* x, double* z);
void mat_proj(double* n, double* v, double* w);
void mat_print(FILE* out, char* desc, double** m);

#endif
