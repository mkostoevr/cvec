//
// The example program uses resize functions.
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

	// Show info
	printf("Capacity: %d, size: %d\n", cvec_char_capacity(&line), cvec_char_size(&line));

	// Fill it with three '?'
	cvec_char_assign_fill(&line, 3, '?');

	// Show info
	printf("Filled by '???'\n%.*s\nCapacity: %d, size: %d\n", cvec_char_size(&line), line, cvec_char_capacity(&line), cvec_char_size(&line));

	// Resize it filling by ???
	cvec_char_resize_v(&line, 6, '!');

	// Show info
	printf("Resized to 6 with '!'\n%.*s\nCapacity: %d, size: %d\n", cvec_char_size(&line), line, cvec_char_capacity(&line), cvec_char_size(&line));

	// Resize it again
	cvec_char_resize(&line, 32);

	// Print it
	puts(line);

	// Show info
	printf("Just resized\n%.*s\nCapacity: %d, size: %d\n", cvec_char_size(&line), line, cvec_char_capacity(&line), cvec_char_size(&line));

	cvec_char_clear(&line);

	printf("Cleared\n%.*s\nCapacity: %d, size: %d\n", cvec_char_size(&line), line, cvec_char_capacity(&line), cvec_char_size(&line));	
}
