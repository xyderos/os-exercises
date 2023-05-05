#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#include "switch.h"

void
demonstrate_context_switch(void)
{
	// if you use the register storage identifier
	// the variable will be stored at the CPU
	// and since no change will be noticed it will be swaping forever
	/*register*/ int done = 0;
	ucontext_t one;
	ucontext_t two;

	getcontext(&one);

	printf("hello \n");

	if (!done) {
		done = 1;
		swapcontext(&two, &one);
	}
}
