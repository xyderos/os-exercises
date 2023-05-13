#define _GNU_SOURCE
#include <sys/types.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "signals.h"

static volatile int done, count;

static sig_atomic_t sigflag = 0;

static void
handler_1(int sig)
{
	printf("signal %d was caught\n", sig);
	return;
}

static void
handler_2(int sig, siginfo_t *siginfo, void *context)
{

	printf("signal %d was caught \n", sig);

	printf("your UID is %d\n", siginfo->si_uid);
	printf("your PID is %d\n", siginfo->si_pid);

	done = 1;
}

static void
handler_3(int sig_no, siginfo_t *info, void *cntx)
{
	ucontext_t *context = (ucontext_t *)cntx;
	unsigned long pc = context->uc_mcontext.gregs[REG_RIP];

	printf("Illegal instruction at 0x%lx value 0x%x\n", pc, *(int *)pc);

	// bypass the faulty instruction and move on to the execution by the
	// next line of code
	context->uc_mcontext.gregs[REG_RIP] = pc + 1;
}

static void
handler_4(int sig)
{
	printf("signal %d received %d times\n", sig, count);
	count++;
}

static void
handler_5(void)
{
	sigflag = 1;
}

static int
raise_fault(void)
{
	int x = 0;
	return 1 % x;
}

void
catch_signal(void)
{
	struct sigaction sa;

	sa.sa_handler = handler_1;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	// can we catch FPE signals?

	sigaction(SIGFPE, &sa, NULL);

	// what is happening after line 37 can cause a signal raise and our
	// handler will catch it

	raise_fault();

	printf("dead code");
}

void
catch_signal_improved(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_2;

	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);

	while (!done) {
	}

	printf("alive code");
}

void
catch_signal_more_improvements(void)
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_3;

	sigemptyset(&sa.sa_mask);

	sigaction(SIGSEGV, &sa, NULL);

	asm(".word 0x00000000");

here:
	printf("Nothing illegal here, we passed the illegal instruction");
	return;
}

void
catch_signal_multiple_times(void)
{
	struct sigaction sa;

	sa.sa_handler = handler_4;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) != 0) {
		return;
	}

	while (count != 4) {
	}
	return;
}

void
kill_from_other_process(void)
{
	struct sigaction act;
	sigset_t cont_mask, old_mask;
	pid_t cpid;

	act.sa_handler = handler_5;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return;

	sigemptyset(&cont_mask);
	sigaddset(&cont_mask, SIGUSR1);

	if (sigprocmask(SIG_BLOCK, &cont_mask, &old_mask) == -1)
		return;

	cpid = fork();

	if (cpid == 0) {
		printf("hello\n");
		kill(getppid(), SIGUSR1);
	} else {
		while (sigflag == 0)
			sigsuspend(&old_mask);
		printf("goodbye\n");
	}
}
