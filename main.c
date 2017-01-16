#include "main.h"

int main(int argc, char **argv) {

    clock_t start = clock();

    TRAINING_SET *training_set = load_training_set("c:\\temp\\trainingset.txt");

    printf("Loading process took %0.3f\n", diffInMs(clock(), start));

    printf("Training set input[%d] output [%d]\n", training_set->input_size, training_set->output_size);

    start = clock();

    CIRCUIT_DESCRIPTOR *circuit_descriptor = generate_random_circuit(training_set, 300);

    printf("Circuit generation took %0.3f\n", diffInMs(clock(), start));

    start = clock();

    evaluate(circuit_descriptor, training_set);

    printf("Total Hits [%d] Size [%d]\n", circuit_descriptor->grades[0], circuit_descriptor->grades[1]);

    printf("Circuit evaluation took %0.3f\n", diffInMs(clock(), start));
    exit(EXIT_SUCCESS);
}


