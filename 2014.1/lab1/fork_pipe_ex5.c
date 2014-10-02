#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int status;
    int var = 1;
    int fd[2];

    if (pipe(fd) < 0) {
        puts("Erro ao abrir pipes");
        exit(-1);
    }

    if (fork() != 0) {
        write(fd[1], &var, sizeof(int));
        wait(&status);
        read(fd[0], &var, sizeof(int));
        printf("Resultado = %d\n", var);
    } else {
        read(fd[0], &var, sizeof(int));
        var++;
        write(fd[1], &var, sizeof(int));
        exit(0);
    }
    return 0;
}

