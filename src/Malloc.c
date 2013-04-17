/**
 * This file defines the improved malloc function.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#include "Malloc.h"

/**
 * A function that defines a malloc wrapper.
 *
 * @param size_t is a size to pass to malloc.
 * @return a pointer to the newly allocated space.
 */
void* Malloc(size_t size) {
    void* malloc_p = malloc(size);

    if (malloc_p == NULL) {
        free(malloc_p);
        printf("Insufficient memory. Failed to allocate space.");
        exit(1);
    }
    return malloc_p;
}
