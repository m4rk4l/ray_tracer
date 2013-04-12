/**
 * Tester for my matrix library
 */

#include "matlib.h"

int main(void) {
    fprintf(stdout, "MATRIX LIBRARY TESTER\n");
    mat_print(stdout, "identity matrix:\n", IDENT_MAT, SIZE);
    return EXIT_SUCCESS;
}
