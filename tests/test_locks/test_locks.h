#include <check.h>

#include "../../src/locks/c_list.h"
#include "../../src/locks/futex.h"
#include "../../src/locks/list.h"
#include "../../src/locks/peterson.h"
#include "../../src/locks/s_list.h"
#include "../../src/locks/swap.h"

Suite *locks_suite(void);

START_TEST(TEST_C_LIST)
{
	bench_c_list(3, 10);
}
END_TEST

START_TEST(TEST_FUTEX)
{
	demonstrate_futex(10);
}
END_TEST

START_TEST(TEST_LIST)
{
	bench_list(3, 10);
}
END_TEST

START_TEST(TEST_PETERSON)
{
	demonstrate_peterson(10);
}
END_TEST

START_TEST(TEST_S_LIST)
{
	bench_s_list(3, 10);
}
END_TEST

START_TEST(TEST_SWAP)
{
	demonstrate_swap(10);
}
END_TEST
