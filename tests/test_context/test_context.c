#include "test_context.h"

Suite *
context_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("context");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, TEST_SWITCH);
	tcase_add_test(tc_core, TEST_YIELD);

	suite_add_tcase(s, tc_core);

	return s;
}
