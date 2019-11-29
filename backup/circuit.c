#include "circuit.h"

void propagate_cnode(BYTE *state, CNODE *cnode, BYTE *input, unsigned int i);

signed int compare_circuit_descriptors(CIRCUIT_DESCRIPTOR *c1, CIRCUIT_DESCRIPTOR *c2);

char *port_to_string(CNODE *cnode);

CIRCUIT_DESCRIPTOR *circuit_randomly_generate(TRAINING_SET *training_set, unsigned int size) {

    if (size < training_set->input_size) {
        fprintf(stderr, "Cannot generate a circuit with size lower than input size");
        exit(EXIT_FAILURE);
    }

    ARRAY_LIST_DESCRIPTOR *array_list_descriptor = array_list_create(size);

    int i;
    for (i = 0; i < training_set->input_size; i++) {
        CNODE *cnode = malloc(sizeof(CNODE));
        cnode->type = INPUT;
        cnode->op.s.index = i;

        array_list_add(array_list_descriptor, cnode);
    }

    for (i = training_set->input_size; i < size; i++) {
        array_list_add(array_list_descriptor, generate_random_cnode(array_list_descriptor->size));
    }

    CIRCUIT_DESCRIPTOR *circuit_descriptor = malloc(sizeof(CIRCUIT_DESCRIPTOR));
    circuit_descriptor->grades = NULL;
    circuit_descriptor->array_list_descriptor = array_list_descriptor;

    return circuit_descriptor;
}

CNODE *generate_random_cnode(unsigned int size) {

    CNODE *cnode = malloc(sizeof(CNODE));

    switch(random_interval(0, 6)) {
        case 0:
            cnode->type = AND;
            generate_double_op(&(cnode->op.d), size);
            break;
        case 1:
            cnode->type = NAND;
            generate_double_op(&(cnode->op.d), size);
            break;
        case 2:
            cnode->type = OR;
            generate_double_op(&(cnode->op.d), size);
            break;
        case 3:
            cnode->type = NOR;
            generate_double_op(&(cnode->op.d), size);
            break;
        case 4:
            cnode->type = NOT;
            cnode->op.s.index = random_index(size);
            break;
        case 5:
            cnode->type = MEM;
            cnode->op.s.index = random_index(size);
            break;
        default:
            fprintf(stderr, "Number generated without treatment.");
            exit(EXIT_FAILURE);
    }
    return cnode;
}

void generate_double_op(DOUBLE_OP *double_op, unsigned int size) {
    int v1 = random_index(size);
    int v2;

    while ((v2 = random_index(size)) == v1);

    double_op->left = min(v1, v2);
    double_op->right = max(v1, v2);
}

unsigned int max(unsigned int v1, unsigned int v2) {
    if (v1 >= v2) {
        return v1;
    }
    else {
        return v2;
    }
}

unsigned int min(unsigned int v1, unsigned int v2) {
    if (v1 < v2) {
        return v1;
    }
    else {
        return v2;
    }
}

BYTE *create_state(CIRCUIT_DESCRIPTOR *circuit_descriptor) {
    return calloc(circuit_descriptor->array_list_descriptor->size, sizeof(BYTE));
}

void reset_circuit_state(CIRCUIT_DESCRIPTOR *circuit_descriptor) {
    signed int i;

    for (i=0; i< circuit_descriptor->array_list_descriptor->size; i++) {
            ((CNODE *) circuit_descriptor->array_list_descriptor->array[i])->state = 0x00;
    }
}

void propagate(BYTE *state, CIRCUIT_DESCRIPTOR *circuit_descriptor, STEP *step) {
    unsigned int i;

    for (i = 0; i < circuit_descriptor->array_list_descriptor->size; i++) {
        propagate_cnode(state, (CNODE *) circuit_descriptor->array_list_descriptor->array[i], step->input, i);
    }
}

void propagate_cnode(BYTE *state, CNODE *cnode, BYTE *input, unsigned int i) {

    switch(cnode->type) {
        case INPUT:
            state[i] = input[i];
            break;
        case AND:
            state[i] = state[cnode->op.d.left] & state[cnode->op.d.right];
            break;
        case OR:
            state[i] = state[cnode->op.d.left] | state[cnode->op.d.right];
            break;
        case NAND:
            state[i] = (state[cnode->op.d.left] & state[cnode->op.d.right]) == 0x01 ? 0x00 : 0x01;
            break;
        case NOR:
            state[i] = (state[cnode->op.d.left] | state[cnode->op.d.right]) == 0x01 ? 0x00 : 0x01;
            break;
        case NOT:
            state[i] = (state[cnode->op.s.index]) == 0x01 ? 0x00 : 0x01;
            break;
        case MEM:
            {
            BYTE actual = cnode->state;
            cnode->state = state[cnode->op.s.index];
            state[i] = actual;
            }
            break;
        default:
            fprintf(stderr, "Circuit type not found!");
            exit(EXIT_FAILURE);
    }


}

signed int circuit_compare(void *c1, void *c2) {

    if (c1 == NULL) {
        handle_error("Cannot compare circuits, first one is NULL.");
    }

    if (((CIRCUIT_DESCRIPTOR *) c1)->grades == NULL) {
        handle_error("Cannot compare circuits, first one have no grades.");
    }

    if (c2 == NULL) {
        handle_error("Cannot compare circuits, second one is NULL.");
    }

    if (((CIRCUIT_DESCRIPTOR *) c2)->grades == NULL) {
        handle_error("Cannot compare circuits, second one have no grades.");
    }


    signed int diff = ((CIRCUIT_DESCRIPTOR *) c2)->grades[0] - ((CIRCUIT_DESCRIPTOR *) c1)->grades[0];

    if (diff == 0) {

        diff = ((CIRCUIT_DESCRIPTOR *)c1)->grades[1] - ((CIRCUIT_DESCRIPTOR *)c2)->grades[1];

        if (diff == 0) {
            diff = compare_circuit_descriptors((CIRCUIT_DESCRIPTOR *)c1, (CIRCUIT_DESCRIPTOR *)c2);
        }
    }

    return diff;
}

signed int compare_circuit_descriptors(CIRCUIT_DESCRIPTOR *c1, CIRCUIT_DESCRIPTOR *c2) {

    // printf("P1 %p P2 %p \n", c1, c2);

    signed int diff = 0;

    signed int i;

    for (i=0; i<c1->array_list_descriptor->size; i++) {
        diff = memcmp(c1->array_list_descriptor->array[i], c2->array_list_descriptor->array[i], sizeof(CNODE));
        if (diff != 0) {
            break;
        }
    }

    return diff;
}

/*
signed int compare_circuit_descriptors(void *c1, void *c2) {

    // printf("P1 %p P2 %p \n", c1, c2);

    signed int diff = 0;

    LIST_ITERATOR *i1 = get_iterator(((CIRCUIT_DESCRIPTOR *)c1)->list_descriptor);
    LIST_ITERATOR *i2 = get_iterator(((CIRCUIT_DESCRIPTOR *)c2)->list_descriptor);

    while ((diff == 0) && (has_next(i1))) {
        CNODE *cnode1 = next(i1);
        CNODE *cnode2 = next(i2);

        diff = memcmp(cnode1, cnode2, sizeof(CNODE));
    }

    free(i1);
    free(i2);

    return diff;
} */

void circuit_free(CIRCUIT_DESCRIPTOR *circuit_descriptor) {
    if (circuit_descriptor != NULL) {
        array_list_free(circuit_descriptor->array_list_descriptor);
        free(circuit_descriptor->grades);
        free(circuit_descriptor);
    }
}

char *circuit_to_string(CIRCUIT_DESCRIPTOR *circuit_descriptor) {

    if (circuit_descriptor->array_list_descriptor->size == 0) {
        handle_error("Cannot convert to string an empty string!");
    }

    int actual_size = sizeof(char *) * (circuit_descriptor->array_list_descriptor->size);
    char *circuit_string = malloc(actual_size);
    circuit_string[0] = '\0';

    signed int i;

    for (i=0; i < circuit_descriptor->array_list_descriptor->size; i++) {
        char *it = port_to_string((CNODE *)circuit_descriptor->array_list_descriptor->array[i]);

        int new_size = strlen(circuit_string) + strlen(it) + 3; // One for null plus 2 for \n
        if (new_size > actual_size) {
            circuit_string = realloc(circuit_string, new_size);
        }

        strcat(circuit_string, it);

        if (i < (circuit_descriptor->array_list_descriptor->size - 1)) {
            strcat(circuit_string, "\n");
        }

        free(it);
    }

    return circuit_string;
}


char *port_to_string(CNODE *cnode) {

    char *text = malloc(1000);

    switch(cnode->type) {
        case AND:
            sprintf(text, "AND[%d,%d]", cnode->op.d.left, cnode->op.d.right);
            break;
        case OR:
            sprintf(text, "OR[%d,%d]", cnode->op.d.left, cnode->op.d.right);
            break;
        case NAND:
            sprintf(text, "NAND[%d,%d]", cnode->op.d.left, cnode->op.d.right);
            break;
        case NOR:
            sprintf(text, "NAND[%d,%d]", cnode->op.d.left, cnode->op.d.right);
            break;
        case MEM:
            sprintf(text, "MEM[%d]", cnode->op.s.index);
            break;
        case INPUT:
            sprintf(text, "INPUT[%d]", cnode->op.s.index);
            break;
        case NOT:
            sprintf(text, "NOT[%d]", cnode->op.s.index);
            break;
        default:
            handle_error("Invalid cnode type!");
            break;
    }

    return text;
}


