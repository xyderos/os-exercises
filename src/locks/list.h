#pragma once

typedef struct list_cell {
	int val;
	struct list_cell *next;
} list_cell_t;

typedef struct list_args {
	unsigned long inc, id;
	list_cell_t *list;
} list_args_t;

void bench_list(unsigned long number_of_threads,
    unsigned long number_of_operations);
