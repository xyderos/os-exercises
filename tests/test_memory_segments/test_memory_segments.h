#include <check.h>

#include "../../src/memory_segments/memory_segments.h"

// Based on trace you can see the virtual address space of each mapping eg code
// stack heap data
// read it based on https://www.baeldung.com/linux/proc-id-maps
Suite *memory_segments_suite(void);

START_TEST(TEST_CODE_MEMORY_SEGMENTS)
{
	code();
	trace();
}
END_TEST

START_TEST(TEST_HEAP_MEMORY_SEGMENTS)
{
	heap();
	trace();
}
END_TEST

START_TEST(TEST_STACK_MEMORY_SEGMENTS)
{
	stack();
	trace();
}
END_TEST
