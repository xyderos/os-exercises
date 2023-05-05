#include <check.h>

#include "../../src/context/switch.h"
#include "../../src/context/yield.h"

Suite *context_suite(void);

START_TEST(TEST_SWITCH)
{
	demonstrate_context_switch();
}
END_TEST

START_TEST(TEST_YIELD)
{
	demonstrate_yield();
}
END_TEST
