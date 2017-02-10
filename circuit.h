#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED

#include "trainingset.h"
#include "crandom.h"
#include "arraylist.h"

typedef enum {AND, OR, NAND, NOR, MEM, INPUT, NOT} CTYPE;

typedef struct {
    unsigned int left;
    unsigned int right;
} DOUBLE_OP;

typedef struct {
    unsigned int index;
} SINGLE_OP;

typedef union {
    SINGLE_OP s;
    DOUBLE_OP d;
} OP;


typedef struct cnode {
    CTYPE type;
    OP op;
    BYTE state;
} CNODE;

typedef struct circuit_descriptor {
    unsigned int *grades;
    ARRAY_LIST_DESCRIPTOR *array_list_descriptor;

} CIRCUIT_DESCRIPTOR;


CIRCUIT_DESCRIPTOR *circuit_randomly_generate(TRAINING_SET *training_set, unsigned int size);

CNODE *generate_random_cnode(unsigned int size);

void generate_double_op(DOUBLE_OP *double_op, unsigned int size);

unsigned int max(unsigned int v1, unsigned int v2);
unsigned int min(unsigned int v1, unsigned int v2);

BYTE *create_state(CIRCUIT_DESCRIPTOR *circuit_descriptor);

void reset_circuit_state(CIRCUIT_DESCRIPTOR *circuit_descriptor);

void propagate(BYTE *state, CIRCUIT_DESCRIPTOR *circuit_descriptor, STEP *step);

char *circuit_to_string(CIRCUIT_DESCRIPTOR *circuit_descriptor);

void circuit_free(CIRCUIT_DESCRIPTOR *circuit_descriptor);

signed int circuit_compare(void *c1, void *c2);

#endif // CIRCUIT_H_INCLUDED
