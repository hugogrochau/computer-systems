#include <stdlib.h>
#include "interpreter.h"

void interpret(Scheduler schedule, int type, FILE *in) {
    char nome[255];
    int prio;
    double time;

    while (!feof(in)) {
        fscanf(in, " %*s %s ", nome);
        switch (type) {
            case DIN:
                fscanf(in, "prioridade=%d", &prio);
                schedule(nome, prio, -1);
                break;
            case SJF:
                fscanf(in, "tempoexec=%lf", &time);
                schedule(nome, -1, time);
                break;
            case RR:
                schedule(nome, -1, -1);
            break;
            default:
                printf("ERROR: Invalid type");
                exit(1);
            break;
        }
    }
}   