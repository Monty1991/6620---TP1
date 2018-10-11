#include "output.h"

#include <stdarg.h>
#include <stdio.h>

void printError(const char *error, ...) {
	va_list args;
	va_start(args, error);
	fprintf(stderr, error, args);
	fputc('\n', stderr);
	va_end(args);
}

void printHelp(const char *program_name) {
	printf("Usage: \n"
		"       %s -h\n"
		"       %s -V\n"
		"       %s [options] archivo\n"
		"Options:\n"
		"         -h, --help      Imprime ayuda.\n"
		"         -V, --version   Version del programa.\n"
		"         -o  --output    Archivo de salida.\n"
		"         -n, --numeric   Ordenar los datos numericamente en vez de "
			"alfabeticamente.\n"
		"Examples: \n"
		"          %s -n numeros.txt\n", program_name, program_name,
			program_name, program_name);
}
