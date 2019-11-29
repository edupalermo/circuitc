#include "linkedlist.h"

LIST_DESCRIPTOR *create_list() {
    LIST_DESCRIPTOR *list_descriptor = malloc(sizeof(LIST_DESCRIPTOR));
    list_descriptor->size = 0;
    list_descriptor->head = NULL;
    list_descriptor->tail = NULL;
    return list_descriptor;
}

void add_node(LIST_DESCRIPTOR *list_descriptor, void *data) {

    LIST_NODE *new_list_node = malloc(sizeof(LIST_NODE));
    new_list_node->next = NULL;

    new_list_node->data = data;

    if (list_descriptor->tail == NULL) {
        list_descriptor->head = new_list_node;
        list_descriptor->tail = new_list_node;
    }
    else {
        list_descriptor->tail->next = new_list_node;
        new_list_node->prev = list_descriptor->tail;
        list_descriptor->tail = new_list_node;
    }
    list_descriptor->size++;
}


LIST_ITERATOR *get_iterator(LIST_DESCRIPTOR *list_descriptor) {
    LIST_ITERATOR *list_iterator = malloc(sizeof(LIST_ITERATOR));

    list_iterator->list_node = list_descriptor->head;

    return list_iterator;
}


void *next(LIST_ITERATOR *list_iterator) {
    void *answer = list_iterator->list_node->data;

    list_iterator->list_node = list_iterator->list_node->next;

    return answer;
}

bool has_next(LIST_ITERATOR *list_iterator) {
    return list_iterator->list_node != NULL;
}

void list_free(LIST_DESCRIPTOR *list_descriptor) {

    if (list_descriptor != NULL) {
        LIST_NODE *list_node = list_descriptor->head;

        while (list_node != NULL) {
            LIST_NODE *next = list_node->next;

            free(list_node->data);
            free(list_node);

            list_node = next;
        }

        free(list_descriptor);
    }

}


