#include <stdio.h>

#include "output.h"
#include "process.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		printError("Cantidad insuficiente de argumentos.");
		return  1;
	} else if (argc > 5) {
		printError("Cantidad excesiva de argumentos.");
		return  1;
	}

	return process(argc, argv);
}
