#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGES 8
#define REFS 512 * 10
#define PAGESIZE 4 * 512
#include "pages.h"

void
simulate_pages(void)
{
	clock_t c_start = 0, c_stop = 0;
	long sum = 0;

	for (int pages = 1; pages <= PAGES; pages++) {
		int loops = REFS / pages;

		c_start = clock();
		sum = 0;
		for (int l = 0; l < loops; l++) {
			char *memory = malloc((long)PAGESIZE * PAGES);
			for (int p = 0; p < pages; p++) {
				long ref = (long)p * PAGESIZE;
				// force page to be allocated
				memory[ref] += 1;
				sum += memory[ref];
			}
		}
		c_stop = clock();

		{
			double proc = 0.0;
			proc = ((double)(c_stop - c_start)) / CLOCKS_PER_SEC;

			printf("%d\t %.6f\t %ld\n", pages, proc, sum);
		}
	}
}
