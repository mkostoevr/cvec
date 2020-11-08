//
// The example program prints numbers from 0 to argc. It shows how to create a vector of basic
// type and use it.
//
// More info in cvec.h
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define CVEC_TYPE int
#define CVEC_INST
#include "cvec.h"

int main(int argc, char **argv) {
	// Create a vector of size argc
	int *ints = cvec_int_new(argc);

	// Fill the vector by values from 0 to argc
	for (int i = 0; i < argc; i++) {
		cvec_int_push_back(&ints, i);
	}

	// Print em all
	for (int i = 0; i < argc; i++) {
		printf("%d\n", ints[i]);
	}
}
