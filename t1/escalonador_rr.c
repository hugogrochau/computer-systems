#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "interpreter.h"
#define INTERVAL 200 //ms
#define MAX_POOL_SIZE 255

int p_pool[MAX_POOL_SIZE];
int end = 0;

void schedule(char *nome, int prio, double time) {
	int pid =  fork();
    if (pid == 0) { // filho
    	p_pool[end++] = getpid();
		kill(getpid(), SIGSTOP);
    	execl(nome, nome, NULL);
    }
}

int main(void) {
	int cur;
	interpret(schedule, RR, stdin);
	while (1) {
		if (cur == end)
			cur = 0;
		
		if (cur > 0)
			kill(p_pool[cur-1], SIGSTOP);
		else 
			kill(p_pool[end-1], SIGSTOP);

		kill(p_pool[cur], SIGCONT);
		sleep(INTERVAL/1000);
	}
	return 1;
}

