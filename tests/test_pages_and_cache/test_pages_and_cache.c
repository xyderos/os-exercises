#include "test_pages_and_cache.h"

Suite *
pages_and_cache_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("pages_and_cache");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, TEST_CLOCK);
	tcase_add_test(tc_core, TEST_LRU);
	tcase_add_test(tc_core, TEST_OPTIMAL);
	tcase_add_test(tc_core, TEST_PAGES);
	tcase_add_test(tc_core, TEST_RANDOM);

	suite_add_tcase(s, tc_core);

	return s;
}
