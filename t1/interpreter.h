#define SJF 0
#define DIN 1
#define RR 2

void interpret (Program *programs);
typedef void (*schedule)(char *name, int prio, float time) Scheduler;