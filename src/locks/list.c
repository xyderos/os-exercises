#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "list.h"

#define MAX 100

static list_cell_t sentinel = { MAX, NULL };
static list_cell_t dummy = { -1, &sentinel };
static list_cell_t *global = &dummy;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void
toggle(list_cell_t *lst, int r)
{
	list_cell_t *prev = NULL, *this = lst, *removed = NULL, *new = NULL;

	pthread_mutex_lock(&mutex);

	while (this->val < r) {
		prev = this;
		this = this->next;
	}

	if (this->val == r) {
		prev->next = this->next;
		removed = this;
	} else {

		new = malloc(sizeof(list_cell_t));

		new->val = r;
		new->next = this;
		prev->next = new;
	}
	pthread_mutex_unlock(&mutex);
	if (removed) {
		free(removed);
	}
}

static void *
bench(void *arg)
{
	unsigned long inc = ((list_args_t *)arg)->inc;
	list_cell_t *lstp = ((list_args_t *)arg)->list;

	for (unsigned long i = 0; i < inc; i++) {
		int r = rand() % MAX;
		toggle(lstp, r);
	}
}

void
bench_list(unsigned long number_of_threads, unsigned long number_of_operations)
{
	list_args_t *thra = NULL;
	pthread_t *thrt = NULL;
	struct timespec t_start, t_stop;
	long wall_sec = 0, wall_nsec = 0, wall_msec = 0;

	pthread_mutex_init(&mutex, NULL);

	thra = malloc(number_of_threads * sizeof(list_args_t));

	for (unsigned i = 0; i < number_of_threads; i++) {
		thra[i].inc = number_of_operations;
		thra[i].id = i;
		thra[i].list = global;
	}

	clock_gettime(CLOCK_MONOTONIC_COARSE, &t_start);

	thrt = malloc(number_of_threads * sizeof(pthread_t));

	for (unsigned long i = 0; i < number_of_threads; i++) {
		pthread_create(&thrt[i], NULL, bench, &thra[i]);
	}

	for (unsigned long i = 0; i < number_of_threads; i++) {
		pthread_join(thrt[i], NULL);
	}

	clock_gettime(CLOCK_MONOTONIC_COARSE, &t_stop);

	wall_sec = t_stop.tv_sec - t_start.tv_sec;
	wall_nsec = t_stop.tv_sec - t_start.tv_sec;
	wall_msec = (wall_sec * 1000) + (wall_nsec / 1000000);

	printf("done in %ld ms \n", wall_msec);
}
