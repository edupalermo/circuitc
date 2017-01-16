#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED

#include "trainingset.h"
#include "crandom.h"

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
    LIST_DESCRIPTOR *list_descriptor;

} CIRCUIT_DESCRIPTOR;


CIRCUIT_DESCRIPTOR *generate_random_circuit(TRAINING_SET *training_set, unsigned int size);

CNODE *generate_random_cnode(unsigned int size);

void generate_double_op(DOUBLE_OP *double_op, unsigned int size);

unsigned int max(unsigned int v1, unsigned int v2);
unsigned int min(unsigned int v1, unsigned int v2);

BYTE *create_state(CIRCUIT_DESCRIPTOR *circuit_descriptor);

void reset_circuit_state(CIRCUIT_DESCRIPTOR *circuit_descriptor);

void propagate(BYTE *state, CIRCUIT_DESCRIPTOR *circuit_descriptor, STEP *step);

signed int compare_circuits(CIRCUIT_DESCRIPTOR *c1, CIRCUIT_DESCRIPTOR *c2);

void circuit_free(CIRCUIT_DESCRIPTOR *circuit_descriptor);

signed int compare_circuit_descriptors(void *c1, void *c2);

#endif // CIRCUIT_H_INCLUDED
