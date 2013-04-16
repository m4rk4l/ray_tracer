/**
 * This file defines the functions for the list structs.
 *
 * @author Marco Anton, Ben Dana
 * @version 4.01.13
 */
#include "list.h"

/** Function declarations */

/**
 * "constructor" for a list object, should simulate a linked list.
 *
 * @return my_list, an allocated list.
 */
list_t* list_init() {
    list_t* my_list = (list_t*)Malloc(sizeof(list_t));

    my_list->head = NULL;
    my_list->tail = NULL;

    return my_list;
}

/**
 * Adds an object structure to a list.
 *
 * @param list is a list where new object is going to be added.
 * @param new_obj is an object structure to be added to list.
 */
void list_add(list_t* list, obj_t* new_obj) {
    if (NULL == list->head) {// when the list is empty. list != NULL?
        list->head = new_obj;
        list->tail = new_obj;
    } else {// if list is not empty
        list->tail->next = new_obj;
        list->tail = list->tail->next;
    }
}

/**
 *
 */
void list_destroy(list_t* list) {
    obj_t* root = list->head;
    if (root != NULL) {
        list->head = root->next;
        root->free_obj(root);
        free(root);
        root = list->head;
        list_destroy(list);
    }
}
