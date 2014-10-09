#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "interpreter.h"
#define INTERVAL 1 //ms

int compare(const void *a, const void *b) {
    Process * pa = (Process *) a;
    Process * pb = (Process *) b;
    return pa->priority > pb->priority;
}

int main(void) {
    Process p_pool[MAX_POOL_SIZE];
    int i, status;
    int num_process = interpret(p_pool, PRI, stdin);
    qsort(p_pool, num_process, sizeof(Process), compare);
    for (i = 0; i < num_process; i++) {
        printf("pid: %d, prioridade: %d\n", p_pool[i].pid, p_pool[i].priority);
        if (i > 0)
            kill(p_pool[i-1].pid, SIGKILL);
        kill(p_pool[i].pid, SIGCONT);
        waitpid(p_pool[i].pid, &status, 0);
    }
    kill(p_pool[i].pid, SIGKILL);
    return 0;
}
