#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED

#include "global.h"
#include "circuit.h"
#include "util.h"
#include "evaluation.h"


void population_evolve(ARRAY_LIST_DESCRIPTOR *population, TRAINING_SET *training_set, float mills_limit);

ARRAY_LIST_DESCRIPTOR *population_generate_inital(unsigned int population_size, unsigned int circuit_size, TRAINING_SET *training_set);

void population_dump(ARRAY_LIST_DESCRIPTOR *population, unsigned int top);

#endif // POPULATION_H_INCLUDED
