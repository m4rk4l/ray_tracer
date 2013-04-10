#ifndef VECLIB_H
#define VECLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 3

double dot3(double* vec1, double* vec2);
void scale3(double scale, double* vecin, double* vecout);
double length3(double* vec);
void diff3(double* vecmin, double* vecsub, double* vecdiff);
void sum3(double* vec1, double* vec2, double* vecsum);
void unitvec(double* vec1, double* vec2);
void vecprn3(double* vec);

#endif
