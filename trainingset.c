#include "trainingset.h"

void internal_load_training_set(TRAINING_SET *training_set, const char *filename);
void fill_step(char *line, TRAINING_SET *training_set, SOLUTION *solution);
int get_input_size(char *line);
int get_output_size(int input_size, char *line);
BYTE *get_input_array(TRAINING_SET *training_set, char *line);
BYTE *get_output_array(TRAINING_SET *training_set, char *line);



TRAINING_SET *load_training_set(const char *filename) {
    TRAINING_SET *training_set = malloc(sizeof(TRAINING_SET));
    training_set->solutions = create_list();
    training_set->input_size = 0;
    training_set->output_size = 0;

    internal_load_training_set(training_set, filename);

    return training_set;
}

void internal_load_training_set(TRAINING_SET *training_set, const char *filename) {
    FILE *inputFile = fopen(filename, "r");

    if (inputFile == NULL)
        exit(EXIT_FAILURE);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    SOLUTION *solution = NULL;

    while ((read = readline(&line, &len, inputFile)) != -1) {
        if (line[0] == '-') { // Starts a new solution
            solution = malloc(sizeof(SOLUTION));
            solution->steps = create_list();

            add_node(training_set->solutions, solution);
        }
        else {
            fill_step(line, training_set, solution);
        }
    }

    if (line != NULL) {
        free(line);
    }

    fclose(inputFile);
}

void fill_step(char *line, TRAINING_SET *training_set, SOLUTION *solution) {

    if (training_set->input_size == 0) {
        training_set->input_size = get_input_size(line);
        training_set->output_size = get_output_size(training_set->input_size, line);
    }

    STEP *step = malloc(sizeof(STEP));

    step->input = get_input_array(training_set, line);
    step->output = get_output_array(training_set, line);

    add_node(solution->steps, step);
}

int get_input_size(char *line) {

    int i = 2;
    int total = 0;

    while (line[i] != 'O') {
        total++;
        i+=2;
    }

    return total;
}


int get_output_size(int input_size, char *line) {
    int i = input_size * 2 + 4;
    int len = strlen(line);

    int total = 0;

    while (i < len) {
        i+= 2;
        total++;
    }

    return total;
}

BYTE *get_input_array(TRAINING_SET *training_set, char *line) {
    BYTE *input = malloc(sizeof(BYTE) * training_set->input_size);

    int i;
    for (i =0; i < training_set->input_size; i++) {
        if (line[(2 * i) + 2] == '0') {
            input[i] = 0;
        }
        else {
            input[i] = 1;
        }
    }
    return input;
}

BYTE *get_output_array(TRAINING_SET *training_set, char *line) {
    BYTE *output = malloc(sizeof(BYTE) * training_set->output_size);
    int i;
    for (i =0; i < training_set->output_size; i++) {
        if (line[(2 * i) + (2 * (training_set->input_size + 1))] == '0') {
            output[i] = 0;
        }
        else {
            output[i] = 1;
        }
    }
    return output;
}

