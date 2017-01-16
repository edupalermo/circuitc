#ifndef TRAININGSET_H_INCLUDED
#define TRAININGSET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "linkedlist.h"
#include "cstream.h"

typedef struct step
{
    BYTE *input;
    BYTE *output;
} STEP;

typedef struct solution
{
    LIST_DESCRIPTOR *steps;
} SOLUTION;

typedef struct training_set
{
    unsigned int input_size;
    unsigned int output_size;
    LIST_DESCRIPTOR *solutions;
} TRAINING_SET;

TRAINING_SET *load_training_set(const char *filename);

#endif // TRAININGSET_H_INCLUDED
