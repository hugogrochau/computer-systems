#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "interpreter.h"
#define INTERVAL 1 //ms

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
    int cur = 0;
    int prev = 0;
    int num_process = interpret(p_pool, RR, stdin);
    while (1) {
        if (num_process == 0) // no processes to execute
            break;

        if (cur == num_process) // reached end of list, going back to the start
            cur = 0;
        
        prev = cur > 0 ? cur - 1 : num_process - 1;
      
        if (num_process > 1) {
            kill(p_pool[prev].pid, SIGSTOP);
        }        

        if (pid_exists(p_pool[cur].pid)) {
            kill(p_pool[cur].pid, SIGCONT);
        } else {
            remove_from_array(p_pool, cur, num_process);
            num_process--;
            cur--;
        }
        

        sleep(INTERVAL);
        cur++;
    }
    return 0;
}
