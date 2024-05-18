//
// The example program prints command line into stdout.
// During printing it will inform us each time vector is reallocated.
// Try to make CVEC_LOGG bigger to see how lesser times reallocation happened
//
// More info in cvec.h
//

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CVEC_TYPE char
#define CVEC_INST
// Override reallocator to look at allocations count
#define CVEC_REALLOC(ptr, size) (printf("Reallocated to %lu\n", size), realloc(ptr, size));
#define CVEC_LOGG 1.5 // Grow by multiplying by 1.5 each time vector gets out of space
#include "cvec.h"

int main(int argc, char **argv) {
	// Create a vector of size 0
	char *line = cvec_char_new(0);

	// Fill it by characters from command line arguments
	for (int i = 0; i < argc; i++) {
		for (int j = 0; j < strlen(argv[i]); j++) {
			cvec_char_push_back(&line, argv[i][j]);
		}
		cvec_char_push_back(&line, ' '); // Separate arguments in the line by spaces
	}

	// Zero-terminate the line
	cvec_char_push_back(&line, '\0');

	// Print the result
	puts(line);
}
