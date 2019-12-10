
#ifndef PROTOCOL_H
#define PROTOCOL_H

#define E_VERSION_NOT_SUPPORTED 1

#define STATUS_OK 200

typedef struct {
	char message[256];
} cir_echo_request;

typedef struct {
	int status;
	char message[256];
} cir_echo_response;

#endif
