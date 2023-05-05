#pragma once

typedef struct lru_pte {
	int id;
	int present;
	struct lru_pte *next;
	struct lru_pte *prev;
} lru_pte_t;

void simulate_lru(unsigned long references, unsigned long pages);
