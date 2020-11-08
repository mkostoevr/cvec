//
// The example program prints command line arguments in separated lines using reserve method to
// reserve space for the vector's elements and iterates over the vector using size method.
// It results to Out Of Bounds access.
//
// More info in cvec.h
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef char *pchar;

#define CVEC_TYPE pchar
#define CVEC_INST
#include "cvec.h"

int main(int argc, char **argv) {
	// Create a vector of initial size 0
	char **args = cvec_pchar_new(0);

	// Reserve space for argc elements
	cvec_pchar_reserve(&args, argc);

	// Fill it by command line arguments
	for (int i = 0; i < argc; i++) {
		cvec_pchar_push_back(&args, argv[i]);
	}

	// Print em all using size method to get the size of the vector
	for (int i = 0; i < cvec_pchar_size(&args); i++) {
		puts(args[i]);
	}
}
