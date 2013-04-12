/**
 * Tester for my matrix library
 */

#include "matlib.h"

int main(void) {
    fprintf(stdout, "MATRIX LIBRARY TESTER\n");
    double ident_mat[][3] = {{1, 0, 0},{1, 0, 0},{1, 0, 0}};
    mat_print(stdout, "identity matrix:\n", ident_mat, SIZE);
    return EXIT_SUCCESS;
}
