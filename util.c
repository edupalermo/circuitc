#include "util.h"

float diffInMs(clock_t end, clock_t start) {
    return ((float)(end - start) / 1000.0F);
}
