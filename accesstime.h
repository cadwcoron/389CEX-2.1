#pragma once
#include <stdio.h>
#include <stdlib.h>
int8_t* generate_random_list( int size, int bound);

int* generate_random_index_list( int size, int bound);

struct timespec diff(struct timespec start, struct timespec end);
