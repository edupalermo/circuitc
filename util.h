#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include<time.h>

#define m_max(i1, i2) i1 > i2 ? i1 : i2

float diffInMs(clock_t end, clock_t start);

#endif // UTIL_H_INCLUDED
