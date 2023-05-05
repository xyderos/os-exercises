#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "clock.h"
#include "utils.h"

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

static void
clear_page_table(clock_pte_t *page_table, unsigned long pages)
{
	for (unsigned long i = 0; i < pages; i++) {
		page_table[i].present = 0;
	}
}

static unsigned long
simulate(clock_pte_t *table, unsigned long *seq, unsigned long references,
    unsigned long frames, unsigned long pages)
{
	unsigned long hits = 0, allocated = 0, next = 0;
	clock_pte_t *last = NULL, *entry = NULL, *cand = NULL;

	for (unsigned long i = 0; i < references; i++) {

		next = seq[i];
		entry = &table[next];

		if (entry->present) {
			entry->referenced = 1;
			hits++;
		} else {
			if (allocated < frames) {
				allocated++;
				entry->present = 1;

				if (!last) {
					last = entry;
					last->next = last;
				} else {
					entry->next = last->next->next;
					last->next = entry;
					last = entry;
				}

			} else {
				cand = last->next;

				while (cand->referenced) {
					cand->referenced = 0;
					last = cand;
					cand = cand->next;
				}
				cand->present = 0;
				cand->referenced = 0;

				entry->present = 1;
				entry->referenced = 0;

				entry->next = cand->next;
				last->next = entry;
				last = entry;
				cand->next = NULL;
			}
		}
	}
	return hits;
}

void
simulate_clock(unsigned long references, unsigned long pages)
{
	clock_pte_t *table = (clock_pte_t *)malloc(pages * sizeof(clock_pte_t));
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
