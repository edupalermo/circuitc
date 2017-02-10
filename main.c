#include "main.h"

#define POPULATION_LIMIT 10000

#define CYCLE_MS 10000


ARRAY_LIST_DESCRIPTOR *generate_inital_population(unsigned int size, TRAINING_SET *training_set);

void dump_population(ARRAY_LIST_DESCRIPTOR *population, unsigned int top);

void evolve_population(ARRAY_LIST_DESCRIPTOR *population, TRAINING_SET *training_set);

int main(int argc, char **argv) {

    srand(time(NULL));

    clock_t start = clock();

    TRAINING_SET *training_set;

    if (argc == 0) {
        training_set = load_training_set("./training_set_java.txt");
    }
    else {
        training_set = load_training_set(argv[1]);
    }

    printf("Loading process took %0.3f\n", diffInMs(clock(), start));

    printf("Training set input[%d] output [%d]\n", training_set->input_size, training_set->output_size);

    start = clock();

    ARRAY_LIST_DESCRIPTOR *population = population_generate_inital(POPULATION_LIMIT, 400, training_set);

    printf("Population generation took %0.3f\n", diffInMs(clock(), start));

    population_dump(population, 30);

    signed int i;
    for (i = 0 ; i < 10; i ++) {
        population_evolve(population, training_set, CYCLE_MS);
        population_dump(population, 30);
    }


//    printf("\nBetter circuit\n");
//    char *better = circuit_to_string(population->array[0]);
//    printf("%s\n", better);
//    free(better);

    exit(EXIT_SUCCESS);
}


