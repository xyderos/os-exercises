#include "utils.h"

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

void
initialize(unsigned long *sequence, unsigned long references,
    unsigned long pages)
{
	unsigned long high = (unsigned long)(pages * ((long double)HIGH / 100));

	for (unsigned long i = 0; i < references; i++) {
		if (rand() % 100 < FREQ) {
			sequence[i] = rand() % high;
		} else {
			sequence[i] = high + rand() % (pages - high);
		}
	}
}
