#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "memory_allocation.h"

static chunk_t *flist = NULL;

void *
memory_allocate(size_t size)
{
	chunk_t *next = flist, *prev = NULL;
	void *memory = NULL;

	if (size == 0) {
		return NULL;
	}

	while (next) {
		if (next->size >= size) {
			if (prev) {
				prev->next = next->next;
			} else {
				flist = next->next;
			}
			return (void *)(next + 1);
		} else {
			prev = next;
			next = next->next;
		}
	}
	// use sbrk to allocate new memory
	memory = sbrk((intptr_t)size + (intptr_t)sizeof(chunk_t));

	if (memory == (void *)-1) {
		return NULL;
	} else {
		chunk_t *cnk = (chunk_t *)memory;
		cnk->size = size;
		return (void *)(cnk + 1);
	}
}

void
memory_free(void *memory)
{
	if (memory) {
		chunk_t *cnk = (chunk_t *)((chunk_t *)memory - 1);
		cnk->next = flist;
		flist = cnk;
	}
	return;
}
