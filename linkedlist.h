#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "general.h"

typedef struct list_node {
    struct list_node *prev;
    void *data;
    struct list_node *next;
} LIST_NODE;

typedef struct list_descriptor {
    unsigned int size;
    struct list_node *head;
    struct list_node *tail;
} LIST_DESCRIPTOR;

typedef struct list_iterator {
    LIST_NODE *list_node;
} LIST_ITERATOR;


LIST_DESCRIPTOR *create_list();

void add_node(LIST_DESCRIPTOR *list_descriptor, void *data);

// Iterator methods
LIST_ITERATOR *get_iterator(LIST_DESCRIPTOR *list_descriptor);
void *next(LIST_ITERATOR *list_iterator);
bool has_next(LIST_ITERATOR *list_iterator);



#endif // LINKEDLIST_H_INCLUDED
