#include "misc.h"

/**
 * parses a line from a file for a format.
 * @param in is a file to read from
 * @param output is an array containing the return values
 * @param format is the format that we are looking for (%d, %lf, etc)
 * @param size is the amout of input we are looking for.
 * @return the amount of elements read.
 * output must have a size of size.
 * In other words what this function does is to read 'size' amount of inputs
 * of the format 'format' from an 'in' file and put them in an outpu array.
 * size must always be 3 or smaller.
 */
int parse_doubles(FILE* in, double* output, char* format, int size) {
//    int ans = 0;
    char line[LINE_SIZE];
    int read;
    int done = 1;

    while (done != 0 && fgets(line, LINE_SIZE, in) != NULL) {
        read = sscanf(line, format, &output[0], &output[1], &output[2]);
        if (read == size) {
            done = 0;
        } else {
            read = -1;
        }
    }

    return read;
/*
    if(fgets(line, LINE_SIZE, in) != NULL) {
        //Always going to try to read at most 3 'things'
        //sscanf returns EOF on failure.
        read = sscanf(line, format, &output[0], &output[1], &output[2]);
        if(read != size) {
            ans = -1;
        }
    } else {
        ans = -2;
    }
    
    return ans;
*/
}

/**
 * The main difference between this funciton and parse_ints is that this one
 * parses for ints while parse_doubles parses for doubles. tried to do this
 * into one function, but it was giving me some errors when moving doubles
 * into ints.
 * @param in for input
 * @param output for putting the parsing elements.
 * @param format a format to parse "%d..."
 * @param size amount of elemets to read. should match %d's from format.
 * @return amount of elements read.
 */
int parse_ints(FILE* in, int* output, char* format, int size) {
//    int ans = 0;
    char line[LINE_SIZE];
    int read;
    int done = 1;

    while (done != 0 && fgets(line, LINE_SIZE, in) != NULL) {
        read = sscanf(line, format, &output[0], &output[1], &output[2]);
        if (read == size) {
            done = 0;
        } else {
            read = -1;
        }
    }

    return read;
/**
    if(fgets(line, LINE_SIZE, in) != NULL) {
        //Always going to try to read at most 3 'things'
        //sscanf returns EOF on failure.
        read = sscanf(line, format, &output[0], &output[1], &output[2]);
        if(read != size) {
            ans = -1;
        }
    } else {
        ans = -2;
    }

    return ans;
*/
}
