/**
 * Tester for my matrix library
 */

#include <stdio.h>
#include <stdlib.h>
#include "matlib.h"

int main(void) {
    fprintf(stdout, "MATRIX LIBRARY TESTER\n");
    double[][3] = {(1, 0, 0),(1, 0, 0),(1, 0, 0)};
    mat_print(stdout, "identity matrix: ", IDENT_MAT);
    return EXIT_SUCCESS;
}
