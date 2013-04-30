#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 128 /** define a size for a line buffer. */
#define VECTOR_SIZE 3 /** defines a vector size */
#define SCALE_RGB 255 /** defines the rgb intensity*/
#define SCALE_RGB_MIN 0.0
#define SCALE_RGB_MAX 1.0

#define ALMOST_ZERO 0.0000001
#define PI 3.14159265359
#define MOD 0

/** Maybe have a parsing function here, but too complicated... */
int parse_doubles(FILE* in, double* output, char* format, int size);
int parse_ints(FILE* in, int* output, char* format, int size);

#endif
