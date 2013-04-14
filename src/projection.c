#ifndef PROJECTION_C
#define PROJECTION_C

#include "projection.h"


/** method declarations */
static int parse_proj(FILE* in, proj_t* proj);
static int check_arguments(int argc, char** argv);

/**
 * used to initialize a projection structure.
 * @param width width of the screen
 * @param height height of the screen
 * @param input is the remaining of the information to be parsed.
 */
proj_t* projection_init(int argc, char** argv, FILE* input) {
    proj_t* proj = (proj_t*)Malloc(sizeof(proj_t));
    int error = 0;

    error += check_arguments(argc, argv);

    if (error == 0) { //arguments are OK.
        proj->win_size_pixel[0] = atoi(argv[1]);// window coord, width (cols)
        proj->win_size_pixel[1] = atoi(argv[2]);// window coord, height (rows)

        error += parse_proj(input, proj);

        if (error != 0) { //error while reading input file.
            printf("### In projection.c\n\tprojection_init: Error while"
                    " parsing for world and view point.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("### In projection.c\n\tprojection_init: Error while reading"
                " arguments.\n");
        exit(EXIT_FAILURE);
    }

    return proj;
}

/**
 * prints projection data to an output file.
 * @param output is a file to print data to.
 * @param proj is a pointer to a projection_type structure
 */
void projection_dump(FILE* out, proj_t* proj) {
    if (out != NULL) {
        fprintf(stderr, "Projection Data dump:\n"
                        "\twindow coord:\t%6.3d\t%6.3d\n"
                        "\tworld coord:\t%6.3lf\t%6.3lf\n"
                        "\tview point:\t%6.3lf\t%6.3lf\t%6.3lf\n",
                        proj->win_size_pixel[0], proj->win_size_pixel[1],
                        proj->win_size_world[0], proj->win_size_world[1],
                        proj->view_point[0], proj->view_point[1],
                                                    proj->view_point[2]);
    } else {
        fprintf(stderr, "#### in projection.c\n\tprojection_dump: file is"
                        " NULL!!!\n");
    }

}

/**
 * map a pixel coordinate to a world coord.
 * @param proj pointer to a projection definition.
 * @param x a pixel coord. width
 * @param y a pixel coord. height
 * @param world pointer to three doubles.
 */
void map_pix_to_world(proj_t* proj, int x, int y, double* world) {
#ifdef DBG_PIX_2_WORLD
    fprintf(stderr, "\nGiven:\n"
                    "\tpixel: (%5.2d, %5.2d)\n"
                    "\tx, y : (%5.2d, %5.2d)\n"
                    "\tworld: (%5.2lf, %5.2lf)\n",
                    proj->win_size_pixel[0], proj->win_size_pixel[1],
                    x, y,
                    proj->win_size_world[0], proj->win_size_world[1]);
#endif
    world[0] = (double) x / (proj->win_size_pixel[0] - 1) *
                                            proj->win_size_world[0];
#ifdef DBG_PIX_2_WORLD
    fprintf(stderr, "\tcur world[0]: %5.2lf\n", world[0]);
#endif
    world[0] -= proj->win_size_world[0] / 2.0;
#ifdef DBG_PIX_2_WORLD
    fprintf(stderr, "\tfinal world[0]: %5.2lf\n", world[0]);
#endif
    world[1] = (double) y / (proj->win_size_pixel[1] - 1) *
                                            proj->win_size_world[1];
#ifdef DBG_PIX_2_WORLD
    fprintf(stderr, "\tcur world[1]: %5.2lf\n", world[1]);
#endif
    world[1] -= proj->win_size_world[1] / 2.0;
#ifdef DBG_PIX_2_WORLD
    fprintf(stderr, "\tfinal world[1]: %5.2lf\n", world[1]);
#endif
    
    world[2] = 0.0;
}

/**
 * Checks for the command line arguments.
 * @param argc is the amount of arguments passed in.
 * @param argv is a double array containing the values of the arguments.
 * @return amount of errors that occured in this function.
 */
static int check_arguments(int argc, char** argv) {
    int error = 0;
    if (argc != ARGS) { // case where no args were given
        printf("usage: %s <widht> <height>\n", argv[0]);
        printf("#### in projection.c:\n\tcheck_arguments: argc != 3\n");
        error++;
    }
    /*TODO: possible improvement is to check the arguments to see if they are 
     * ints with isdigit func from ctype.h */
    return error;
}

/**
 * parses a file for window coordinates and view point coordinates.
 * @param in is an input file to parse.
 * @param proj is a structure where staff read is gona be put.
 */
static int parse_proj(FILE* in, proj_t* proj) {
    int error = 0;
    if (in != NULL) { // check if in is not NULL.
        error -= parse_doubles(in, proj->win_size_world, "%lf%lf",
                                                            VECTOR_SIZE - 1);
        error -= parse_doubles(in, proj->view_point, "%lf%lf%lf",
                                                                VECTOR_SIZE);
    } else {
        fprintf(stderr, "#### in projection.c\n\tparse: file is NULL!!!\n");
    }
    return error;
}

#endif
