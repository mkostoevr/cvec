//
// The example program prints command line arguments in separated line but makes +-1 mistake.
// It results to Out Of Bounds access.
// Since handler of Oub Of Bounds acces (CVEC_OOBH) is configured in the program, after each
// OOB access it will print a message with information.
//
// More info in cvec.h
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef char *pchar;

#define CVEC_TYPE pchar
#define CVEC_INST
// Set Out Of Bounds handler
#define CVEC_OOBH(funcname, vec, index) printf("Out of bounds in %s (vec = %p, i = %d)", funcname, vec, index)
#include "cvec.h"

int main(int argc, char **argv) {
	// Create a vector of size argc
	char **args = cvec_pchar_new(argc);

	// Fill it by command line arguments
	for (int i = 0; i < argc; i++) {
		cvec_pchar_push_back(&args, argv[i]);
	}

	// Print em all but get our of bounds using <= instead of <
	for (int i = 0; i <= cvec_pchar_size(&args); i++) {
		// Use at method to get an element with bounds checking
		// At some point it will detect Out Of Bounds access and call our OOB handler
		puts(cvec_pchar_at(&args, i));
	}
}
