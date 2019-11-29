#ifndef RECEIVER_H_INCLUDED
#define RECEIVER_H_INCLUDED

#include <stdio.h> //printf, NULL
#include <stdlib.h> //malloc
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h> //memset
#include <pthread.h>

void *receiver_start(void *arg);

#endif // RECEIVER_H_INCLUDED
