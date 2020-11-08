//
// The example program prints command a sequence of numbers.
// The numbers are copied into the vector using assign_* methods.
//
// More info in cvec.h
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CVEC_TYPE char
#define CVEC_INST
#include "cvec.h"

int main(int argc, char **argv) {
	char *msg = "Hello, world!";

	// Create a vector of size 0
	char *line = cvec_char_new(0);

	// Fill it by characters from command line arguments
	cvec_char_assign_range(&line, msg, msg + strlen(msg) + 1);

	// Print the result
	puts(line);

	// Show info
	printf("Capacity: %d, size: %d\n", cvec_char_capacity(&line), cvec_char_size(&line));

	// Now fill it with '?'
	cvec_char_assign_fill(&line, 3, '?');
	cvec_char_push_back(&line, '\0');

	// Print it
	puts(line);

	// Show info
	printf("Capacity: %d, size: %d\n", cvec_char_capacity(&line), cvec_char_size(&line));
}
