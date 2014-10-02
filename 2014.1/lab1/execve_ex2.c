#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int status;
    char *temp[] = {"hang", "5", NULL};

    if (fork() != 0) {
        printf("meu PID = %d\n", (int) getpid());
        wait(&status);
    } else {
        printf("meu PID = %d\n", (int) getpid());

        execve("fork", temp, NULL);
        exit(0);
    }
    return 0;
}
/* Que o seu programa imprimiu? Faz sentido? 
 * O programa imprimiu o pid do pai depois o do filho
 * ai o filho executou o programa `fork` mantendo seu pid
 * pois não foi um fork. 
 *
 */
