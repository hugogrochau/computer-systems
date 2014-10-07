#define SJF 0
#define DIN 1
#define RR 2

#define MAX_POOL_SIZE 255

#include <stdio.h>

typedef int (*Scheduler)(char *name, int prio, double time);
int interpret (int *p_pool, Scheduler schedule, int type, FILE* in);