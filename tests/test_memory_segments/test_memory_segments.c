#include "test_memory_segments.h"

Suite *
memory_segments_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("memory_segments");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, TEST_CODE_MEMORY_SEGMENTS);
	tcase_add_test(tc_core, TEST_HEAP_MEMORY_SEGMENTS);
	tcase_add_test(tc_core, TEST_STACK_MEMORY_SEGMENTS);

	suite_add_tcase(s, tc_core);

	return s;
}
