#include "arraylist.h"

ARRAY_LIST_DESCRIPTOR *array_list_create(unsigned int initial_size) {
    ARRAY_LIST_DESCRIPTOR *new_array_list = malloc(sizeof(ARRAY_LIST_DESCRIPTOR));
    if (!new_array_list) {
        handle_error("Fail to allocate memory for the descriptor of a new array list.");
    }

    new_array_list->size = 0;
    new_array_list->mod_count = 0;
    new_array_list->max = initial_size;

    new_array_list->array = malloc(initial_size * sizeof(void *));

    return new_array_list;
}

void array_list_add(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, void *data) {
    array_list_insert(array_list_descriptor, array_list_descriptor->size, data);
}

void *array_list_get(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, unsigned int index) {

    if (array_list_descriptor == NULL) {
        handle_error("Tying to get an element from a null array_list descriptor!");
    }

    if (index >= array_list_descriptor->size) {
        handle_error("Invalid access to index %d on array_list of max size %d", index, array_list_descriptor->size);
    }

    return array_list_descriptor->array[index];
}

void array_list_insert(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, unsigned int index, void *data) {

    if (array_list_descriptor == NULL) {
        handle_error("Tying to add an element to a null array_list descriptor");
    }

    if (index > array_list_descriptor->size) {
        handle_error("Invalid index [%d] used on insert in the array_list with size [%d]", index, array_list_descriptor->size);
    }

    if (array_list_descriptor->max == array_list_descriptor->size) {
        array_list_descriptor->max = m_max((array_list_descriptor->max + 1), (unsigned int)(array_list_descriptor->max * 1.1f));
        array_list_descriptor->array = realloc(array_list_descriptor->array, array_list_descriptor->max * sizeof(void *));

        if (!array_list_descriptor->array) {
            handle_error("Fail to reallocate allocate array for an array_list.");
        }
    }

    if (index < array_list_descriptor->size) {
        size_t data_size = sizeof(void *);
        void *insert_point = (array_list_descriptor->array + (index * data_size));
        memcpy(insert_point + data_size , insert_point, (array_list_descriptor->size - index) * data_size);
    }

    array_list_descriptor->array[index] = data;

    array_list_descriptor->size++;
    array_list_descriptor->mod_count++;
}

signed int array_list_oredered_add_if_unique(ARRAY_LIST_DESCRIPTOR *array_list_descriptor, COMPARATOR comparator, void *data) {

    if (array_list_descriptor == NULL) {
        handle_error("Tying to ordered add an element to a null array_list descriptor");
    }


    signed int min = -1;
    signed int max = array_list_descriptor->size;

    signed int index;

    if (max - min == 1) {
        index = 0;
    }
    else {
        do  {
            index = min + ((max - min) / 2);

            signed int compare_result = comparator(array_list_descriptor->array[index], data);

            if (compare_result == 0) {
                index = -1;
            }
            else if (compare_result > 0) {
                max = index;
            }
            else {
                min = index;
            }

        } while ((max - min > 1) && (index != -1));
        index = max;
    }


    if (index != -1) {
        array_list_insert(array_list_descriptor, index, data);
    }

    return index;
}


