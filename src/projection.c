#include "projection.h"

/** method declarations */
static int check_arguments(int argc, char** argv);
static double randpix(int value);

/**
 * used to initialize a projection structure.
 * @param width width of the screen
 * @param height height of the screen
 * @param input is the remaining of the information to be parsed.
 */
proj_t* projection_init(int argc, char** argv, FILE* input) {
    proj_t* proj = (proj_t*)Malloc(sizeof(proj_t));
    int rc = 0;

    rc += check_arguments(argc, argv);

    if (rc == 0) { //arguments are OK.
        proj->win_size_pixel[0] = atoi(argv[1]);// window coord, width (cols)
        proj->win_size_pixel[1] = atoi(argv[2]);// window coord, height (rows)

        rc = parse_doubles(input, proj->win_size_world, "%lf%lf",
                                                            VECTOR_SIZE - 1);
        rc += parse_doubles(input, proj->view_point, "%lf%lf%lf", VECTOR_SIZE);

        if (rc != 5) { //error while reading input file.
            fprintf(stderr, "### In projection.c\n\t"
                            "projection_init: Error while"
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
#ifdef ALIASING
    double rx;
    double ry;
    rx = randpix(x);
    ry = randpix(y);
    world[0] = (1.0 * rx / proj->win_size_pixel[0]) * proj->win_size_world[0];
    world[0] = (1.0 * ry / proj->win_size_pixel[1]) * proj->win_size_world[1];
    world[2] = 0.0;
#else
    world[0] = (double) x / (proj->win_size_pixel[0] - 1) *
                                            proj->win_size_world[0];
    world[0] -= proj->win_size_world[0] / 2.0;
    world[1] = (double) y / (proj->win_size_pixel[1] - 1) *
                                            proj->win_size_world[1];
    world[1] -= proj->win_size_world[1] / 2.0;
    
    world[2] = 0.0;
#endif
}

/**
 * comes up with a random position of a pixel.
 * @param value is a seed value for the random function.
 */
static double randpix(int value) {
    srandom(value);
    return random();
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
    randpix(1);// to get rid of warning of not using randpix
    /*TODO: possible improvement is to check the arguments to see if they are 
     * ints with isdigit func from ctype.h */
    return error;
}

/**
 *
 */
void free_proj(proj_t* proj) {
    free(proj);
}
