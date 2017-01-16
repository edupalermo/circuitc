#include "main.h"

#define POPULATION_LIMIT 10000

ARRAY_LIST_DESCRIPTOR *generate_inital_population(unsigned int size, TRAINING_SET *training_set);

void dump_population(ARRAY_LIST_DESCRIPTOR *population, unsigned int top);

int main(int argc, char **argv) {

    srand(time(NULL));

    clock_t start = clock();

    //TRAINING_SET *training_set = load_training_set("c:\\temp\\trainingset.txt");
    TRAINING_SET *training_set = load_training_set("c:\\temp\\training_set_java.txt");

    printf("Loading process took %0.3f\n", diffInMs(clock(), start));

    printf("Training set input[%d] output [%d]\n", training_set->input_size, training_set->output_size);

    start = clock();

    ARRAY_LIST_DESCRIPTOR *population = generate_inital_population(500, training_set);

    printf("Population generation took %0.3f\n", diffInMs(clock(), start));

    dump_population(population, 30);

    //start = clock();


//    printf("Total Hits [%d] Size [%d]\n", circuit_descriptor->grades[0], circuit_descriptor->grades[1]);

//    printf("Circuit evaluation took %0.3f\n", diffInMs(clock(), start));
    exit(EXIT_SUCCESS);
}

ARRAY_LIST_DESCRIPTOR *generate_inital_population(unsigned int size, TRAINING_SET *training_set) {
    int i;

    ARRAY_LIST_DESCRIPTOR *population = array_list_create(POPULATION_LIMIT);

    for (i = 0; i < size; i++) {
        CIRCUIT_DESCRIPTOR *circuit_descriptor = generate_random_circuit(training_set, 300);
        evaluate(circuit_descriptor, training_set);

        if (array_list_oredered_add_if_unique(population, &compare_circuit_descriptors, circuit_descriptor) == -1) {
            circuit_free(circuit_descriptor);
        }
    }

    return population;
}

void dump_population(ARRAY_LIST_DESCRIPTOR *population, unsigned int top) {
    unsigned int i;
    char message[256];

    for (i = 0; i < top; i++) {
        CIRCUIT_DESCRIPTOR *circuit_descriptor = array_list_get(population, i);
        sprintf(message, "Hits [%d] Size [%d]", circuit_descriptor->grades[0], circuit_descriptor->grades[1]);
        printf("[%d] %s\n", i+1, message);
    }
}


