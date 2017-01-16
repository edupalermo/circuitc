#include "error.h"

void handle_error(const char *format, ...) {
    va_list ap;
    va_start(ap, format);

    fprintf(stderr, "ERROR program interrupted!\n");
    fprintf(stderr, format, ap);

    va_end(ap);

    exit(EXIT_FAILURE);
}
