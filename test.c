#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define CVEC_TYPE int
#define CVEC_INST
#include "cvec.h"

#define check(cond) do { \
	if (!(cond)) { \
		fprintf(stderr, "Check failed at %s:%d\n", __FILE__, __LINE__); \
		exit(-1); \
	} \
} while (0)

void check_push_back(size_t final_size, size_t initial_size) {
	assert(final_size > initial_size);

	fprintf(stderr, "%s(%lu, %lu): ", __func__, final_size, initial_size);

	// Create an empty vector
	int *ints = cvec_int_new(0);
	check(cvec_int_size(&ints) == 0);
	check(cvec_int_capacity(&ints) == 0);
	check(cvec_int_empty(&ints));

	// Fill the first part manually
	cvec_int_resize(&ints, initial_size);
	check(cvec_int_size(&ints) == initial_size);
	check(cvec_int_capacity(&ints) == initial_size);
	for (int i = 0; i < initial_size; i++) {
		ints[i] = i;
	}

	// Fill the rest using push_back
	for (int i = initial_size; i < final_size; i++) {
		cvec_int_push_back(&ints, i);
	}
	check(cvec_int_size(&ints) == final_size);
	check(cvec_int_capacity(&ints) >= final_size);

	// Check em all
	for (int i = 0; i < final_size; i++) {
		check(ints[i] == i);
	}

	fprintf(stderr, "OK\n");
}

void check_pop_back(size_t vector_size) {
	fprintf(stderr, "%s(%lu): ", __func__, vector_size);

	// Create an empty vector
	int *ints = cvec_int_new(0);
	check(cvec_int_size(&ints) == 0);
	check(cvec_int_capacity(&ints) == 0);
	check(cvec_int_empty(&ints));

	// Fill the vector manually
	cvec_int_resize(&ints, vector_size);
	check(cvec_int_size(&ints) == vector_size);
	check(cvec_int_capacity(&ints) == vector_size);
	for (int i = 0; i < vector_size; i++) {
		ints[i] = i;
	}

	// Pop back all elements from the vector
	for (int i = vector_size - 1; i >= 0; i--) {
		check(cvec_int_pop_back(&ints) == i);
		check(cvec_int_size(&ints) == i);
	}

	fprintf(stderr, "OK\n");
}

void check_pop_front(size_t vector_size) {
	fprintf(stderr, "%s(%lu): ", __func__, vector_size);

	// Create an empty vector
	int *ints = cvec_int_new(0);
	check(cvec_int_size(&ints) == 0);
	check(cvec_int_capacity(&ints) == 0);
	check(cvec_int_empty(&ints));

	// Fill the vector manually
	cvec_int_resize(&ints, vector_size);
	check(cvec_int_size(&ints) == vector_size);
	check(cvec_int_capacity(&ints) == vector_size);
	for (int i = 0; i < vector_size; i++) {
		ints[i] = i;
	}

	// Pop front all elements from the vector
	for (int i = 0; i < vector_size; i++) {
		check(cvec_int_pop_front(&ints) == i);
		check(cvec_int_size(&ints) == vector_size - i - 1);
	}

	fprintf(stderr, "OK\n");
}

int main(int argc, char **argv) {
	check_push_back(1000, 0);
	check_push_back(1000, 500);
	check_pop_back(1000);
	check_pop_front(1000);
}
