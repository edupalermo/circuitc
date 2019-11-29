#include "population.h"


void population_evolve(ARRAY_LIST_DESCRIPTOR *population, TRAINING_SET *training_set, float mills_limit) {

    clock_t start = clock();

    while (diffInMs(clock(), start) < mills_limit) {

        CIRCUIT_DESCRIPTOR *new_circuit_descriptor = circuit_randomly_generate(training_set, 300);
        evaluation_evaluate(new_circuit_descriptor, training_set);

        if (
            (circuit_compare(new_circuit_descriptor, population->array[population->size - 1]) > 0) ||
            (array_list_oredered_add_if_unique(population, &circuit_compare, new_circuit_descriptor) == -1)
            ) {
            printf("free\n");
            circuit_free(new_circuit_descriptor);
        }
    }

}

ARRAY_LIST_DESCRIPTOR *population_generate_inital(unsigned int population_size, unsigned int circuit_size, TRAINING_SET *training_set) {
    int i;

    ARRAY_LIST_DESCRIPTOR *population = array_list_create(population_size);

    for (i = 0; i < population_size; i++) {
        CIRCUIT_DESCRIPTOR *circuit_descriptor = circuit_randomly_generate(training_set, circuit_size);
        evaluation_evaluate(circuit_descriptor, training_set);

        if (array_list_oredered_add_if_unique(population, &circuit_compare, circuit_descriptor) == -1) {
            circuit_free(circuit_descriptor);
        }
    }

    return population;
}


void population_dump(ARRAY_LIST_DESCRIPTOR *population, unsigned int top) {
    unsigned int i;
    char message[256];

    for (i = 0; i < top; i++) {
        CIRCUIT_DESCRIPTOR *circuit_descriptor = array_list_get(population, i);
        sprintf(message, "Hits [%2d] Size [%d]", circuit_descriptor->grades[0], circuit_descriptor->grades[1]);
        printf("[%2d] %s\n", i+1, message);
    }
    printf("Population Size %d\n\n", population->size);
}
