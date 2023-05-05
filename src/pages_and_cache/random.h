#pragma once

typedef struct random_pte {
	int present;
} random_pte_t;

void simulate_random(unsigned long references, unsigned long pages);
