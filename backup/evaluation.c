#include "evaluation.h"

void evaluate_hits(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set, int index);

unsigned int count_hits(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set);

void evaluate_size(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set, int index);

unsigned int **allocate_score(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set);

unsigned int totalize_hits(unsigned int **score, unsigned int circuit_length, unsigned int output_size);

void count_hits_from_solution(CIRCUIT_DESCRIPTOR *circuit_descriptor, SOLUTION *solution, unsigned int **score, unsigned int output_size);

void increment_score(unsigned int **score, unsigned int circuit_length, BYTE *state, BYTE *output, unsigned int output_size);

void evaluation_evaluate(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set) {
    // If there is evaluation, clean it
    if (circuit_descriptor->grades != NULL) {
        free(circuit_descriptor->grades);
    }

    circuit_descriptor->grades = calloc(2, sizeof(unsigned int));

    evaluate_hits(circuit_descriptor, training_set, 0);
    evaluate_size(circuit_descriptor, training_set, 1);

}


void evaluate_hits(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set, int index) {
    circuit_descriptor->grades[index] = count_hits(circuit_descriptor, training_set);
}

unsigned int count_hits(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set) {
    unsigned int **score = allocate_score(circuit_descriptor, training_set);

    LIST_ITERATOR *list_iterator = get_iterator(training_set->solutions);

    while (has_next(list_iterator)) {
        SOLUTION *solution = next(list_iterator);
        count_hits_from_solution(circuit_descriptor, solution, score, training_set->output_size);
    }

    free(list_iterator);

    unsigned int total = totalize_hits(score, circuit_descriptor->array_list_descriptor->size, training_set->output_size);

    free(score);
    return total;
}

unsigned int **allocate_score(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set) {

    unsigned int circuit_size = circuit_descriptor->array_list_descriptor->size;

    unsigned int **score = calloc(circuit_size, sizeof(unsigned int *));

    unsigned int i = 0;

    for (i = 0; i < circuit_size ; i++) {
        score[i] = calloc(training_set->output_size, sizeof(unsigned int));

        unsigned int j;

        for (j = 0; j < training_set->output_size; j++) {
            score[i][j] = 0;
        }
    }

    return score;
}

void count_hits_from_solution(CIRCUIT_DESCRIPTOR *circuit_descriptor, SOLUTION *solution, unsigned int **score, unsigned int output_size) {
    BYTE *state = create_state(circuit_descriptor);
    reset_circuit_state(circuit_descriptor);

    LIST_ITERATOR *steps_iterator = get_iterator(solution->steps);
    while (has_next(steps_iterator)) {
        STEP *step = next(steps_iterator);
        propagate(state, circuit_descriptor, step);

        increment_score(score, circuit_descriptor->array_list_descriptor->size, state, step->output, output_size);
    }

    free(steps_iterator);
}

unsigned int totalize_hits(unsigned int **score, unsigned int circuit_length, unsigned int output_size) {
    unsigned int total = 0;

    unsigned int i , j;

    for (j = 0; j < output_size; j++) {
        int max = 0;
        for (i = 1; i < circuit_length; i++) {
            if (score[i][j] > score[max][j]) {
                max = i;
            }
        }
        total += score[max][j];
    }

    return total;
}

void increment_score(unsigned int **score, unsigned int circuit_length, BYTE *state, BYTE *output, unsigned int output_size) {
    int i, j;

    for (i = 0; i < circuit_length; i++) {
        for (j = 0; j < output_size; j++) {
            if (state[i] == output[j]) {
                score[i][j]++;
            }
        }
    }
}


void evaluate_size(CIRCUIT_DESCRIPTOR *circuit_descriptor, TRAINING_SET *training_set, int index) {
    circuit_descriptor->grades[index] = circuit_descriptor->array_list_descriptor->size;
}
