#ifndef ARRAYLIST_H_INCLUDED
#define ARRAYLIST_H_INCLUDED

#include <string.h> //memcpy
#include <stdio.h> //printf

#include "error.h"
#include "util.h"


typedef signed int (*COMPARATOR)(void *,void *);

typedef void (*FREE_ARRAY_LIST_DATA)(void *);



typedef struct array_list_descriptor {

    unsigned int size;

    unsigned int max;

    unsigned int mod_count;

    void **array;

    FREE_ARRAY_LIST_DATA free_array_list_data;

} ARRAY_LIST_DESCRIPTOR;



ARRAY_LIST_DESCRIPTOR *array_list_create(unsigned int initial_size);

void array_list_add(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, void *data);

void *array_list_get(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, unsigned int index);

void array_list_insert(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, unsigned int index, void *data);

signed int array_list_oredered_add_if_unique(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, COMPARATOR comparator, void *data);

#endif // ARRAYLIST_H_INCLUDED
