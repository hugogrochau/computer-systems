#include "program.h"
#include "interpreter.h"
#include <stdio.h>
#include <error.h>

void interpret(Scheduler schedule, int type) {
    char nome[255];
    int prio;
    float time;

    while (!feof(stdin)) {
        scanf(" %s %s ", NULL, nome);
        switch (type) {
            case DIN:
                scanf("%d", &prio);
                schedule(nome, prio, -1);
                break;
            case SJF:
                scanf("%lf", &time);
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