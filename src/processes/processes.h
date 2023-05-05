#pragma once

// parent died, child is still alive
void orphan(void);

// child process is terminated
int zombie(void);

// the parent waits until the child has finished executing another process
void wait_proc(void);

// each process from fork keeps private memory
void private_memory(void);
