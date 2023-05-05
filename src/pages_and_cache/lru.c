#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lru.h"
#include "utils.h"

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

static void
clear_page_table(lru_pte_t *page_table, unsigned long pages)
{
	for (unsigned long i = 0; i < pages; i++) {
		page_table[i].present = 0;
	}
}

static unsigned long
simulate(lru_pte_t *table, unsigned long *seq, unsigned long references,
    unsigned long frames, unsigned long pages)
{
	unsigned long hits = 0, allocated = 0, i = 0, next = 0;
	lru_pte_t *first = NULL, *last = NULL, *entry = NULL, *evict = NULL;

	for (i = 0; i < references; i++) {

		next = seq[i];
		entry = &table[next];

		if (entry->present) {
			hits++;

			if (entry->next) {
				entry->next->prev = entry->prev;
			} else {
				last = entry->prev;
			}
			if (entry->prev) {
				entry->prev->next = entry->next;
			} else {
				first = entry->next;
			}
			entry->next = NULL;
			entry->prev = NULL;

			if (last) {
				last->next = entry;
			}
			entry->prev = last;
			last = entry;
		} else {
			if (allocated < frames) {
				allocated++;

				entry->present = 1;
				entry->prev = last;
				entry->next = NULL;
				if (last) {
					last->next = entry;
				}
				if (!first && !last) {
					last = entry;
					first = last;
				} else {
					last = entry;
				}
			} else {
				evict = first;
				if (evict->next) {
					evict->next->prev = evict->prev;
				}
				if (evict->prev) {
					evict->prev->next = evict->next;
				} else {
					first = evict->next;
				}
				evict->next = NULL;
				evict->prev = NULL;
				evict->present = 0;

				entry->present = 1;
				entry->prev = last;
				entry->next = NULL;
				if (last != NULL) {
					last->next = entry;
				}
				last = entry;
			}
		}
	}
	return hits;
}

void
simulate_lru(unsigned long references, unsigned long pages)
{
	lru_pte_t *table = (lru_pte_t *)malloc(pages * sizeof(lru_pte_t));
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
