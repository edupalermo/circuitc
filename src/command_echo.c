
int process_command_echo(cir_client_context *client_context) {

	int version;

	if (read_completely(client_context->socket, &version, size(int)) == -1) {
		return -1;
	}

	switch (version) {
		case 1 :
			process_command_echo_v1(client_context);
			break;
		default :
			return E_VERSION_NOT_SUPPORTED;
	}


}

int process_command_echo_v1(cir_client_context *client_context) {

	cir_echo_request request;

	int skip = 2 * sizeof(int);

	if (read_completely(client_context->socket, &request + skip, size(cir_echo_request) - skip) == -1) {
		return -1;	
	}

	cir_echo_response response;
	response.status.type = STATUS_OK;
	if (strlen(request.message) + 15 > ) {
	}
		

	

}

int read_completely(int socket, void *buffer, int size) {
	int total = 0;
	do {
		int read = read(socket, buffer + total, size - total);
		if (read == -1) {
			return read;
		}
		total += read;
	} while (total < size);
	return total;
}
