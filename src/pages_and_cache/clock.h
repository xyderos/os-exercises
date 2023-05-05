#pragma once

typedef struct clock_pte {
	int id;
	int present;
	int referenced;
	struct clock_pte *next;
} clock_pte_t;

void simulate_clock(unsigned long references, unsigned long pages);
