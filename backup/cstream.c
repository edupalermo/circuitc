#include "cstream.h"

int readline(char **lineptr, size_t *n , FILE *stream) {

    if ((*lineptr == NULL) || (*n == 0)) {
        *n = 255;
        *lineptr = malloc(sizeof(char) * *n);
        if (*lineptr == NULL) {
            fprintf(stderr, "Unnable to allocate memory for readline.\n");
            exit(EXIT_FAILURE);
        }
    }

    int read = 0;

    char c;

    do {
        if (read >= (*n - 1)) {
            fprintf(stderr, "Realocation not implemented in readline.\n");
            exit(EXIT_FAILURE);
        }
        c = fgetc(stream);

        if (c == EOF) {
            if (read == 0) {
                read = -1;
            }
            else {
                printf("Not implemented, reading a file without ending with a EOL");
                exit(EXIT_FAILURE);
            }
        }
        else {
            if ((c == CR) || (c == LF)) { // End of line

                (*lineptr)[read] = '\0';
                read++; // Counting from CRLF

                if (c == CR) {
                    c = fgetc(stream);
                    read++;
                }
            }
            else {
                (*lineptr)[read ++] = c;
            }
        }
    } while ((c != LF) && (c != CR) && (c != EOF));



    return read;

}

