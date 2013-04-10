#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "Malloc.h"
#include "object.h"

typedef struct list_type {
    obj_t* head; /** pointer to first object in list */
    obj_t* tail; /** pointer to last object in list*/
} list_t;

list_t* list_init();

void list_add(list_t* list, obj_t* new_obj);

void list_destroy(list_t* list);
#endif
