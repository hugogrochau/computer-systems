#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include "interpreter.h"
#define INTERVAL 1 //ms

int compare(const void *a, const void *b) {
    Process * pa = (Process *) a;
    Process * pb = (Process *) b;
    return pa->priority > pb->priority;
}

void remove_from_array(Process *p_pool, int index, int size) {
    int i;
    for (i = index; i < size - 1; i++)
        p_pool[index] = p_pool[index + 1];
}   

int pid_exists(int pid) {
    int status;
    return pid != waitpid(pid, &status, WNOHANG);
}

int main(void) {

    Process p_pool[MAX_POOL_SIZE];
    int num_process = interpret(p_pool, PRI, stdin);
    int current = -1;


    qsort(p_pool, num_process, sizeof(Process), compare);

    while (1) {

        printf("num_process: %d \n", num_process);
        if (num_process == 0) // no processes to execute
            break;

        if (num_process > 1 && current >= 0 && current != p_pool[0].pid) {
            printf("Parando o processo de PID: %d \n",  current);

            kill(current, SIGSTOP);
        }

        current = p_pool[0].pid;

        if (pid_exists(p_pool[0].pid)) {

            printf("Executando e diminuindo a prioridade do processo de PID: %d e prioridade: %d \n",  p_pool[0].pid, p_pool[0].priority);

            kill(p_pool[0].pid, SIGCONT);
            if (p_pool[0].priority < 7) 
                p_pool[0].priority++;

        } else {
            printf("Removendo o processo de PID: %d \n", p_pool[0].pid);
            remove_from_array(p_pool, 0, num_process);
            num_process--;
            current = -1;
        }

        sleep(INTERVAL);

        if (num_process > 1)
            qsort(p_pool, num_process, sizeof(Process), compare);

    }
    return 0;
}
