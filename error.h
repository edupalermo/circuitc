#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <stdlib.h> //EXIT_FAILURE
#include <stdio.h> // fprintf
#include <stdarg.h> // va_start, va_end

void handle_error(const char *format, ...);

#endif // ERROR_H_INCLUDED
