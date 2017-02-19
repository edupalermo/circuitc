#include "main.h"

ARRAY_LIST_DESCRIPTOR *generate_inital_population(unsigned int size, TRAINING_SET *training_set);

void dump_population(ARRAY_LIST_DESCRIPTOR *population, unsigned int top);

void evolve_population(ARRAY_LIST_DESCRIPTOR *population, TRAINING_SET *training_set);

int main(int argc, char **argv) {

    // Load some information if needed
    // ========================================
    srand(time(NULL)); // This will provide different random number per run


    // Trigger threads
    // ========================================
    // Server Socket to receive circuits
    //pthread_t receiver_thread;
    //pthread_create(&receiver_thread, NULL, &receiver_start, NULL);

    pthread_t hive_thread;
    pthread_create(&hive_thread, NULL, &hive_start, NULL);



    // Join active threads
    // ========================================
    printf("Waiting hive thread to finish...\n");
    pthread_join(hive_thread, NULL);
    printf("Hive thread to finish!\n");

    // Finishing
    // ========================================


    exit(EXIT_SUCCESS);
}


