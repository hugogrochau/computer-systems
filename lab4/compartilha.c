#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main (void) { 
    pid_t pid1 = 0, pid2 = 0;
    int s = 1, status;

    if (fork() == 0)  { // filho 1
        pid1 = getpid();
        sleep(4);
        execl("./io_bound", "./io_bound", NULL);
        if (fork() == 0)  { // filho 2
            pid2 = getpid();
            sleep(4);
            execl("/bin/cat", "/bin/cat", "exec.c", NULL);
        } else { // pai
            while(1) {
                printf("%d %d\n", pid1, pid2);
                if (s) {
                    kill(SIGSTOP, pid1);
                    kill(SIGCONT, pid2);
                } else {
                    kill(SIGSTOP, pid2);
                    kill(SIGCONT, pid1);
                }
                s = !s;
            }
        }
    }
    return 0;
}
