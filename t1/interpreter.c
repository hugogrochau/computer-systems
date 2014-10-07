#include <stdlib.h>
#include "interpreter.h"

int interpret(int *p_pool, Scheduler schedule, int type, FILE *in) {
    char nome[255];
    int prio;
    double time;
    int num_process = 0;

    while (!feof(in)) {
        fscanf(in, " %*s %s ", nome);
        switch (type) {
            case DIN:
                fscanf(in, "prioridade=%d", &prio);
                p_pool[num_process] = schedule(nome, prio, -1);
                break;
            case SJF:
                fscanf(in, "tempoexec=%lf", &time);
                p_pool[num_process] = schedule(nome, -1, time);
                break;
            case RR:
                p_pool[num_process] = schedule(nome, -1, -1);
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