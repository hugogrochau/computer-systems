#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include "interpreter.h"
#include <stdlib.h>
#define INTERVAL 200 //ms


int schedule(char *nome, int prio, double time) {
    int pid =  fork();
    int status;
    if (pid == 0) { // filho
        printf("nome: %s\n", nome);
        execl(nome, nome, NULL);
        exit(0);
    }
    return pid;
}

int main(void) {
    int p_pool[MAX_POOL_SIZE];
    int cur = 0;
    int num_process = interpret(p_pool, schedule, RR, stdin);
    printf("num_process:%d, pid:%d, p_pool[0]:%d, p_pool[1]:%d\n", num_process, getpid(), p_pool[0], p_pool[1]);
    while (1) {
        if (cur == num_process)
            cur = 0;
        
        if (cur > 0)
            kill(p_pool[cur-1], SIGSTOP);
        else 
            kill(p_pool[num_process-1], SIGSTOP);

        kill(p_pool[cur], SIGCONT);
        sleep(1);
        cur++;
    }
    return 1;
}
