#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "memory_segments.h"

// char arrays
char global_char_array[] = "1";
static char static_global_char_array[] = "2";
static const char static_const_global_char_array[] = "3";

// char pointers
char *global_char_ptr = "4";
static char *static_global_char_ptr = "5";
static const char *static_const_global_char_ptr = "6";
// ints
const int const_int = 7;
static const int static_const_int = 8;
int an_int = 9;

void
code(void)
{
foo:
	printf("global_char_array:              %p\n", &global_char_array);
	printf("static_global_char_array:       %p\n",
	    &static_global_char_array);
	printf("static_const_global_char_array: %p\n",
	    &static_const_global_char_array);

	printf("global_char_ptr:                %p\n", &global_char_ptr);
	printf("static_global_char_ptr:         %p\n", &static_global_char_ptr);
	printf("static_const_global_char_ptr:   %p\n",
	    &static_const_global_char_ptr);

	printf("const_int:                      %p\n", &const_int);
	printf("static_const_int:               %p\n", &static_const_int);
	printf("an_int:                         %p\n", &an_int);

	printf("code_segment:                   %p\n", &&foo);
}

void
heap(void)
{
	char *heap_1 = malloc(20);
	*heap_1 = 0x61;

	printf("heap_1:                         %p\n", &heap_1);
	printf("pointing to:                    %p\n", heap_1);
	printf("heap_1 pointing to:             0x%x\n", *heap_1);

	free(heap_1);

	char *foo = malloc(20);
	*foo = 0x62;
	printf("foo pointing to:                0x%x\n", *foo);
	/*DANGER AHEAD*/

	*heap_1 = 0x63;

	printf("or is it pointing to:           0x%x\n", *foo);

	long *heap_2 = (unsigned long *)calloc(40, sizeof(unsigned long));

	int pid = getpid();
	printf("heap_2[2]:                      0x%lx\n", heap_2[2]);
	printf("heap_2[1]:                      0x%lx\n", heap_2[1]);
	printf("heap_2[0]:                      0x%lx\n", heap_2[0]);
	printf("heap_2[-1]:                     0x%lx\n", heap_2[-1]);
	printf("heap_2[-2]:                     0x%lx\n", heap_2[-2]);

	free(heap_2);
	printf("\nheap_2 freed\n\n");

	printf("heap_2[2]:                      0x%lx\n", heap_2[2]);
	printf("heap_2[1]:                      0x%lx\n", heap_2[1]);
	printf("heap_2[0]:                      0x%lx\n", heap_2[0]);
	printf("heap_2[-1]:                     0x%lx\n", heap_2[-1]);
	printf("heap_2[-2]:                     0x%lx\n", heap_2[-2]);
}

void
zot(unsigned long *stop)
{

	unsigned long r = 0x3;

	unsigned long *i;

	for (i = &r; i <= stop; i++) {
		printf("%p 0x%lx \n", i, *i);
	}
}

void
foo(unsigned long *stop)
{
	unsigned long q = 0x2;

	zot(stop);
}

void
stack(void)
{
	unsigned long p = 0x1;

	foo(&p);

back:
	printf("p:                              %p \n", &p);
	printf("back:                           %p \n", &&back);
}

void
trace(void)
{
	int pid = getpid();
	printf("\n\n /proc/%d/maps \n\n", pid);
	char command[50];
	sprintf(command, "cat /proc/%d/maps", pid);
	system(command);
}
