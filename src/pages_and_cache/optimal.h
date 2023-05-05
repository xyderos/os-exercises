#pragma once

typedef struct optimal_pte {
	int present;
} optimal_pte_t;

void simulate_optimal(unsigned long references, unsigned long pages);
