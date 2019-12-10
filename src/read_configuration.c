#include <yaml.h>

#define TYPE_RAM 0
#define TYPE_FILESYSTEM 1

typedef struct {
	char *name;
	unsigned short int type;
	char *path;
	unsigned long int save;
} SOURCE;

typedef struct {
	int size;
	SOURCE *source;
} CONFIGURATION;

CONFIGURATION* read_configuation(char *filename) {

	FILE *file = fopen(filename, "rb");

	CONFIGURATION *configuration = read_configuation_from_file(file);

	close(file);

	return NULL;
}

CONFIGURATION* read_configuation_from_file(FILE *file) {

	yaml_parser_t parser;
	yaml_event_t event;

	int done = 0;

	/* Create the Parser object. */
	yaml_parser_initialize(&parser);

	yaml_parser_set_input_file(&parser, file);

	while (!done) {
		if (!yaml_parser_parse(&parser, &event)) {
			// TODO Exit with error
			break;
		}

		event.data

		done = (event.type == YAML_STREAM_END_EVENT);

		yaml_event_delete(&event);

	}

	return NULL;
}

int read_handler(void *ext, char *buffer, int size, int *length) {
    return 1;
}
