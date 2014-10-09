#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "interpreter.h"

int run(char *nome) {
    int pid =  fork();
    if (pid == 0) { // child
        execl(nome, nome, NULL);
        exit(0);
    }
    kill(pid, SIGSTOP);
    return pid;
}

int interpret(Process *p_pool, int type) {
    char nome[255];
    Process temp;
    int num_process = 0;

    while (!feof(stdin)) {
        fscanf(stdin, " %*s %s ", nome);
        switch (type) {
            case PRI:
                fscanf(stdin, "prioridade=%d", &temp.priority);
                temp.pid = run(nome);
                p_pool[num_process] = temp;
                break;
            case SJF:
                fscanf(stdin, "tempoexec=%lf", &temp.time);
                temp.pid = run(nome);
                p_pool[num_process] = temp;
                break;
            case RR:
                temp.pid = run(nome);
                p_pool[num_process] = temp;
            break;
            default:
                printf("ERROR: Invalid type");
                exit(1);
            break;
        }
        ++num_process;
    }
    return num_process;
}   