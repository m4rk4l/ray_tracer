/**
 * Tester for my matrix library
 */

#include "veclib.h"

#define CROSS 0
#define MULT 1
#define XPOSE 2
#define XFORM 3
#define PROJ 4
#define PRINT 5
#define ROT 6

/** Some func delarations */
void tests();
void print_mat_op(double* v1, double* v2, double* v3, size_t size, int op);

int main(void) {
    printf("MATRIX LIBRARY TESTER\n");
    printf("---------------------\n\n");
    tests();
    return EXIT_SUCCESS;
}

/**
 *
 */
void tests() {


    printf("\n----------------------Printing Test:-----------------------\n");
    print_mat_op(NULL, NULL, NULL, SIZE, PRINT);

    printf("\n-----------------------Normal Test:------------------------\n");
    double vec1[] = {1, 1, 1};
    double vec2[] = {1, 0, -1};
    double vec3[] = {0, 0, 0};
    double mat1[] = {1,2,3, 4,5,6, 7,8,9};
    double mat2[] = {0,1,2, 3,4,5, 6,7,8};
    double mat3[] = {0,0,0, 0,0,0, 0,0,0};

    print_mat_op(vec1, vec2, vec3, SIZE, CROSS);
    print_mat_op(mat1, mat2, mat3, SIZE, MULT);
    print_mat_op(mat1, NULL, mat3, SIZE, XPOSE);
    print_mat_op(mat1, vec1, vec3, SIZE, XFORM);
    print_mat_op(vec1, vec2, mat3, SIZE, ROT);
/**
    printf("\n---------------------Same Pointer Test:--------------------\n");
    print_mat_op(vec1, vec1, vec1, SIZE, CROSS);
    vec1[0]=1; vec1[1]=2; vec1[2]=3;

    print_mat_op(mat1, mat1, mat1, SIZE, MULT);
    mat1[0]=1; mat1[1]=2; mat1[2]=3; mat1[3]=4; mat1[4]=5; mat1[5]=6;
    mat1[6]=7; mat1[7]=8; mat1[8]=9;

    print_mat_op(mat1, NULL, mat1, SIZE, XPOSE);
    mat1[0]=1; mat1[1]=2; mat1[2]=3; mat1[3]=4; mat1[4]=5; mat1[5]=6;
    mat1[6]=7; mat1[7]=8; mat1[8]=9;

    print_mat_op(mat1, vec1, vec1, SIZE, XFORM);
    mat1[0]=1; mat1[1]=2; mat1[2]=3; mat1[3]=4; mat1[4]=5; mat1[5]=6;
    mat1[6]=7; mat1[7]=8; mat1[8]=9;

    printf("\n-------------Same Pointer Test Different values:-----------\n");
    vec1[0] = 1; vec1[1] = 1; vec1[2] = 1;
    print_mat_op(vec1, vec1, vec3, SIZE, CROSS);

    mat1[0]=1; mat1[1]=1; mat1[2]=1; mat1[3]=1; mat1[4]=1; mat1[5]=1;
    mat1[6]=1; mat1[7]=1; mat1[8]=1;
    print_mat_op(mat1, mat1, mat1, SIZE, MULT);

    mat1[0]=1; mat1[1]=1; mat1[2]=1; mat1[3]=1; mat1[4]=1; mat1[5]=1;
    mat1[6]=1; mat1[7]=1; mat1[8]=1;
    print_mat_op(mat1, NULL, mat1, SIZE, XPOSE);

    mat1[0]=1; mat1[1]=1; mat1[2]=1; mat1[3]=1; mat1[4]=1; mat1[5]=1;
    mat1[6]=1; mat1[7]=1; mat1[8]=1;
    print_mat_op(mat1, vec1, vec1, SIZE, XFORM);

    printf("\n----------------------Different Values:--------------------\n");
    vec1[0] = -1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 9; vec2[1] = 8; vec2[2] = 7;
    print_mat_op(vec1, vec2, vec3, SIZE, CROSS);

    mat1[0]=2; mat1[1]=1; mat1[2]=2; mat1[3]=8; mat1[4]=7; mat1[5]=3;
    mat1[6]=8; mat1[7]=4; mat1[8]=7;
    print_mat_op(mat1, mat2, mat3, SIZE, MULT);

    mat1[0]=2; mat1[1]=1; mat1[2]=2; mat1[3]=8; mat1[4]=7; mat1[5]=3;
    mat1[6]=8; mat1[7]=4; mat1[8]=7;
    print_mat_op(mat1, mat2, mat3, SIZE, XPOSE);

    mat1[0]=2; mat1[1]=1; mat1[2]=2; mat1[3]=8; mat1[4]=7; mat1[5]=3;
    mat1[6]=8; mat1[7]=4; mat1[8]=7;
    print_mat_op(mat1, vec1, vec3, SIZE, XFORM);
*/
}

/**
 * depending on which option is given, certain operation will be performed.
 */
void print_mat_op(double* v1, double* v2, double* v3, size_t size, int op) {
    switch (op) {
        case CROSS:
            printf("\tCROSS PRODUCT\n");
            vecprn3(stdout, "\tu =", v1);
            vecprn3(stdout, "\tw =", v2);
            mat_cross(v1, v2, v3, size);
            vecprn3(stdout, "\tu x w =", v3);
        break;
        case MULT:
            printf("\tMULTIPLICATION\n");
            mat_print(stdout, "\tA:\n", v1, SIZE);
            mat_print(stdout, "\tB:\n", v2, SIZE);
            mat_mul(v1, v2, v3, size);
            mat_print(stdout, "\tA * B:\n", v3, SIZE);
        break;
        case XPOSE:
            printf("\tTRANSPOSE\n");
            mat_print(stdout, "\tA:\n", v1, SIZE);
            mat_xpose(v1, v3, SIZE);
            mat_print(stdout, "\tA^T:\n", v3, SIZE);
        break;
        case XFORM:
            printf("\tTRANSFROM\n");
            mat_print(stdout, "\tA:\n", v1, SIZE);
            vecprn3(stdout, "\tu:\n", v2);
            mat_xform(v1, v2, v3, size);
            vecprn3(stdout, "\tA * u:\n", v3);
        break;
        case PROJ:
            printf("\tPROJECTION\n");
        break;
        case PRINT:
            printf("\tPRINT\n");
            //mat_print(stdout, "\tIdentity Matrix:\n", IDENT_MAT, SIZE);
        break;
        case ROT:
            fprintf(stdout, "\tROTATIONAL MATRIX\n");
            vecprn3(stdout, "\tnormal ", v1);
            vecprn3(stdout, "\txdir: ", v2);
            mat_rot(v1, v2, v3);
            mat_print(stdout, "\trotation\n", v3, SIZE);
        break;
        default:
            printf("Invalid operation.\n");
    }
}
