//
// The example program prints command line arguments in separated lines. The vector of pointers
// to characters is instantiated so that names of its methods start from cvec_pchar_, it's done
// after creation of a new type and passing it to cvec header as CVEC_TYPE.
//
// More info in cvec.h
//

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef char *pchar;

#define CVEC_TYPE pchar
#define CVEC_INST
#include "cvec.h"

int main(int argc, char **argv) {
	// Create a vector of size argc
	char **args = cvec_pchar_new(argc);

	// Fill it by command line arguments
	for (int i = 0; i < argc; i++) {
		cvec_pchar_push_back(&args, argv[i]);
	}

	// Print em all
	for (int i = 0; i < argc; i++) {
		puts(args[i]);
	}
}
