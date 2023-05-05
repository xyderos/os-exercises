#include <check.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "driver.h"
#include "test_context/test_context.h"
#include "test_locks/test_locks.h"
#include "test_memory_segments/test_memory_segments.h"
#include "test_pages_and_cache/test_pages_and_cache.h"
#include "test_processes/test_processes.h"

int
main(void)
{
	int no_failed = 0;
	Suite *s = NULL;
	SRunner *runner = NULL;

	s = memory_segments_suite();
	runner = srunner_create(s);
	srunner_add_suite(runner, processes_suite());
	srunner_add_suite(runner, pages_and_cache_suite());
	srunner_add_suite(runner, context_suite());
	srunner_add_suite(runner, locks_suite());

	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
