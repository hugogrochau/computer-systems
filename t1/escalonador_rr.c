#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "interpreter.h"
#define INTERVAL 1 // s

void remove_from_array(Process *p_pool, int index, int size) {
    int i;
    for (i = index; i < size -1; i++)
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
    int output = open("output.txt", O_RDWR | O_CREAT, 0666);
    int input = open("input.txt",  O_RDWR | O_CREAT, 0666);
    int num_process;

    close(0);
    dup(input);

    close(1);
    dup(output);

    num_process = interpret(p_pool, RR);

    while (1) {
        if (num_process == 0) // no processes to execute
            break;

        if (cur == num_process) // reached end of list, going back to the start
            cur = 0;
        

        prev = cur > 0 ? cur - 1 : num_process - 1;
      
        if (num_process > 1) {
            kill(p_pool[prev].pid, SIGSTOP);
            dprintf(output, "Processo de PID: %d foi parado\n", p_pool[prev].pid);
        }        

        if (pid_exists(p_pool[cur].pid)) {
            dprintf(output, "Processo de PID: %d comecou a executar\n", p_pool[cur].pid);
            kill(p_pool[cur].pid, SIGCONT);
        } else {

            dprintf(output, "Processo de PID: %d foi removido\n", p_pool[cur].pid);
            dprintf(output, "antes pid %d num_process %d cur %d prev %d\n", p_pool[cur].pid, num_process, cur, prev);

            remove_from_array(p_pool, cur, num_process);

            num_process--;
            cur--;
            dprintf(output, "depois pid %d num_process %d cur %d prev %d\n", p_pool[cur].pid, num_process, cur, prev);

        }
        
        sleep(INTERVAL);
        cur++;
    }

    return 0;
}
