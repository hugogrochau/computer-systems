#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int status;

    if (fork() != 0) {
        printf("meu PID = %d\n", (int) getpid());
        wait(&status);
    } else {
        printf("meu PID = %d\n", (int) getpid());
        exit(0);
    }
    return 0;
}
