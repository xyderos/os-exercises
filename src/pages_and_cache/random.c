#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "random.h"
#include "utils.h"

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

static void
clear_page_table(random_pte_t *page_table, unsigned long pages)
{
	for (unsigned long i = 0; i < pages; i++) {
		page_table[i].present = 0;
	}
}

static unsigned long
simulate(random_pte_t *table, unsigned long *seq, unsigned long references,
    unsigned long frames, unsigned long pages)
{
	unsigned long hits = 0, allocated = 0, i = 0, next = 0, rnd = 0;
	random_pte_t *entry = NULL, *evict = NULL;

	for (i = 0; i < references; i++) {
		next = seq[i];
		entry = &table[next];

		if (entry->present) {
			hits++;
		} else {
			if (allocated < frames) {
				allocated++;
				entry->present = 1;
			} else {
				do {
					rnd = (unsigned long)rand() % pages;
					evict = &table[rnd];
				} while (!evict->present);
				evict->present = 0;
				entry->present = 1;
			}
		}
	}
	return hits;
}

void
simulate_random(unsigned long references, unsigned long pages)
{
	random_pte_t *table = (random_pte_t *)malloc(
	    pages * sizeof(random_pte_t));
	unsigned long frames = 0, incr = 0, *sequence = NULL, hits = 0;
	double ratio = 0.0;

	sequence = (unsigned long *)malloc(references * sizeof(int));
	initialize(sequence, references, pages);

	incr = pages / SAMPLES;

	for (frames = incr; frames <= pages; frames += incr) {
		clear_page_table(table, pages);
		hits = simulate(table, sequence, references, frames, pages);

		ratio = (double)hits / (double)references;

		printf("%lu\t\t%.2f\n", frames, ratio);
	}
}
