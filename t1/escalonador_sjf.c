#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "interpreter.h"
#define INTERVAL 1 //ms

int compare(const void *a, const void *b) {
    Process * pa = (Process *) a;
    Process * pb = (Process *) b;
    return pa->time > pb->time;
}

int main(void) {
    Process p_pool[MAX_POOL_SIZE];
    int i, status;
	int output = open("output.txt", O_RDWR | O_CREAT, 0666);
	int input = open("input.txt",  O_RDWR | O_CREAT, 0666);
    int num_process;

	close(0);
	dup(input);

	close(1);
	dup(output);

    num_process = interpret(p_pool, SJF);
    qsort(p_pool, num_process, sizeof(Process), compare);
    for (i = 0; i < num_process; i++) {
        if (i > 0){
            kill(p_pool[i-1].pid, SIGKILL);
			dprintf(output, "Processo de PID: %d e duração: %lf terminou de executar\n",  p_pool[i-1].pid, p_pool[i-1].time);
	}
		dprintf(output, "Processo de PID: %d e duração: %lf começou a executar\n",  p_pool[i].pid, p_pool[i].time);
        kill(p_pool[i].pid, SIGCONT);
		
        waitpid(p_pool[i].pid, &status, 0);
    }
	dprintf(output, "Processo de PID: %d e Prioridade: %lf terminou de executar. \n", p_pool[i-1].pid, p_pool[i-1].time);
    kill(p_pool[i].pid, SIGKILL);	
	dprintf(output, "Todos os processos terminaram de executar. \n");
    return 0;
}
