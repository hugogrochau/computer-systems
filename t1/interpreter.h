#define SJF 0
#define PRI 1
#define RR 2

#define MAX_POOL_SIZE 255

#include <stdio.h>

typedef struct process_s {
	int pid;
	int priority;
	double time;
} Process;

int interpret (Process *p_pool, int type, FILE* in);