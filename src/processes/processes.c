#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <unistd.h>

#include "processes.h"

void
orphan(void)
{
	int pid = fork();

	if (pid == 0) {
		int child = getpid();
		printf("child:  parent %d,  group %d\n", getppid(),
		    getpgid(child));
		sleep(4);
		printf("child:  parent %d,  group %d\n", getppid(),
		    getpgid(child));
		sleep(4);
		printf("child:  parent %d,  group %d\n", getppid(),
		    getpgid(child));
		sleep(4);
	} else {
		int parent = getpid();
		printf("parent:  parent %d,  group %d\n", getppid(),
		    getpgid(parent));
		sleep(2);
		int i = 3 / 0;
	}
}

int
zombie(void)
{
	int pid = fork();

	if (pid == 0) {
		printf("check the status\n");
		sleep(1);
		printf("and again (pid:%d)\n", (int)getpid());
		return 10;
	} else {
		sleep(2);
		int res;
		wait(&res);
		printf("The result was %d\n", WEXITSTATUS(res));
		printf("and again (pid:%d)\n", (int)getpid());
		sleep(1);
	}

	printf("That's it %d\n", (int)getpid());
}

void
wait_proc(void)
{
	int pid = fork();

	if (pid == 0) {
		execlp("ls", "ls", NULL);
		printf("this will only happen if exec fails\n");
	} else {
		wait(NULL);
		printf("we're done\n");
	}
}

void
private_memory(void)
{
	int pid;
	int x = 123;
	pid = fork();

	if (pid == 0) {
		sleep(2);
		printf("    child:  x is %d and the address is  0x%p\n", x, &x);
		x = 42;
		sleep(1);
		printf("    child:  x is %d and the address is  0x%p\n", x, &x);
	} else {
		printf("    mother: x is %d and the address is  0x%p\n", x, &x);
		x = 13;
		sleep(1);
		printf("    mother: x is %d and the address is  0x%p\n", x, &x);
		wait(NULL);
	}
}
