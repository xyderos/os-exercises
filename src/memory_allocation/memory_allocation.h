#pragma once

#include <stddef.h>

typedef struct chunk {
	size_t size;
	struct chunk *next;
} chunk_t;

void *memory_allocate(size_t size);

void memory_free(void *memory);
