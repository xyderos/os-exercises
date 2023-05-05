#include "test_processes.h"

Suite *
processes_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("processes");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, TEST_ORPHAN);
	tcase_add_test(tc_core, TEST_ZOMBIE);
	tcase_add_test(tc_core, TEST_WAIT_PROC);
	tcase_add_test(tc_core, TEST_PRIVATE_MEMORY);

	suite_add_tcase(s, tc_core);

	return s;
}
