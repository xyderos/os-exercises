#include <check.h>

#include "../../src/processes/processes.h"

Suite *processes_suite(void);

START_TEST(TEST_ORPHAN)
{
	orphan();
}
END_TEST

START_TEST(TEST_ZOMBIE)
{
	zombie();
}
END_TEST

START_TEST(TEST_WAIT_PROC)
{
	wait_proc();
}
END_TEST

START_TEST(TEST_PRIVATE_MEMORY)
{
	private_memory();
}
END_TEST
