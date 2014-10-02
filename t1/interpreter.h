#define SJF 0
#define DIN 1
#define RR 2

#include <stdio.h>


typedef void (*Scheduler)(char *name, int prio, double time);
void interpret (Scheduler schedule, int type, FILE* in);