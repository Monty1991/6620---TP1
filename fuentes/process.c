#include "process.h"

#include "output.h"
#include "text.h"
#include "version.h"

#include <stdio.h>
#include <stdbool.h>

// Reads file_in, sorts the text and writes to file_out
int processFile(const char *file_in, const char *file_out, bool order_numeric);

int process(int argc, char **argv) {
	bool order_numeric = false;
	char *output_file_name = NULL;

	const char *short_opt = "Vho:n";

	struct option long_opt[] = {
		{"version", no_argument, NULL, 'V'},
		{"help", no_argument, NULL, 'h'},
		{"output", required_argument, NULL, 'o'},
		{"numeric", no_argument, (void *)&order_numeric, true},
		{NULL, 0, NULL,  0}
	};

	int option_index;
	int c;
	while((c = getopt_long(argc, argv, short_opt, long_opt,
		&option_index)) != -1) {
		switch(c) {
			case 'o':
				if (optarg != NULL) {
					if (strcmp(optarg, "-") != 0)
						output_file_name = optarg;
				}
				break;

			case 'n':
				order_numeric = true;
				break;

			case 'V':
				printf("%s\n", VERSION);
				return 0;

			case 'h':
				printHelp(*argv);
				return 0;
		}
	}

	return processFile(argv[argc - 1], output_file_name, order_numeric);
}

int processFile(const char *file_in, const char *file_out,
	bool order_numeric) {
	Text_t text;
	if (textCreate(&text) == TEXT_ERROR) {
		printError("Error al leer crear el objeto text.");
		return 1;
	}

	FILE *input_file = NULL;
	input_file = fopen(file_in, "r");
	if (input_file == NULL) {
		textDestroy(&text);
		printError("Error al abrir el archivo de entrada: %s.", file_in);
		return 1;
	}

	if (textRead(&text, input_file) == TEXT_ERROR) {
		fclose(input_file);
		textDestroy(&text);
		printError("Error al leer el archivo de entrada.");
		return 1;
	}
	fclose(input_file);

	if (textSort(&text, order_numeric) == TEXT_ERROR) {
		textDestroy(&text);
		printError("Error al ordenar texto\n");
		return 1;
	}

	FILE *output_file = NULL;
	if (file_out)
		output_file = fopen(file_out, "w");
	else
		output_file = stdout;

	if (!output_file) {
		textDestroy(&text);
		printError("Error al crear archivo salida <%s>\n", file_out);
		return 1;
	}

	if (textWrite(&text, output_file) == TEXT_ERROR) {
		textDestroy(&text);
		if (output_file != stdout)
			fclose(output_file);
		printError("Error al escribir en archivo salida");
		return 1;
	}

	textDestroy(&text);
	if (output_file != stdout)
		fclose(output_file);

	return 0;
}
