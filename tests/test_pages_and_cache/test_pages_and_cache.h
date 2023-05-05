#include <check.h>

#include "../../src/pages_and_cache/clock.h"
#include "../../src/pages_and_cache/lru.h"
#include "../../src/pages_and_cache/optimal.h"
#include "../../src/pages_and_cache/pages.h"
#include "../../src/pages_and_cache/random.h"

#define REFERENCES 10
#define PAGES 100

Suite *pages_and_cache_suite(void);

START_TEST(TEST_CLOCK)
{
	simulate_clock(REFERENCES, PAGES);
}
END_TEST

START_TEST(TEST_LRU)
{
	simulate_lru(REFERENCES, PAGES);
}
END_TEST

START_TEST(TEST_OPTIMAL)
{
	simulate_optimal(REFERENCES, PAGES);
}
END_TEST

START_TEST(TEST_PAGES)
{
	simulate_pages();
}
END_TEST

START_TEST(TEST_RANDOM)
{
	simulate_random(REFERENCES, PAGES);
}
END_TEST
