#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "optimal.h"
#include "utils.h"

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

static void
clear_page_table(optimal_pte_t *page_table, unsigned long pages)
{
	for (unsigned long i = 0; i < pages; i++) {
		page_table[i].present = 0;
	}
}

static unsigned long
simulate(optimal_pte_t *table, unsigned long *seq, unsigned long references,
    unsigned long frames, unsigned long pages)
{
	unsigned long hits = 0, allocated = 0, i = 0, next = 0, sofar = 0,
		      candidate = 0, dist = 0;
	optimal_pte_t *entry = NULL, *evict = NULL;

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

				candidate = pages;

				for (unsigned long c = 0; c < pages; c++) {
					if (table[c].present) {

						while (seq[i + dist] != c &&
						    i + dist < references) {
							dist++;
						}
						if (dist > sofar) {
							candidate = c;
							sofar = dist;
						}
					}
				}
				evict = &table[candidate];

				evict->present = 0;
				entry->present = 1;
			}
		}
	}
	return hits;
}

void
simulate_optimal(unsigned long references, unsigned long pages)
{
	optimal_pte_t *table = (optimal_pte_t *)malloc(
	    pages * sizeof(optimal_pte_t));
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
