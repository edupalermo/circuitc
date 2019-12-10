
typedef struct _cir_client_context {
	pthread_t thread_id;
	int socket;
} cir_client_context;

void *clientHandler(void *vargp);
