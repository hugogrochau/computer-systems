#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int status;
    const char text[] = "Hello World";
    char dados[12];
    int fd[2];

    if (pipe(fd) < 0) {
        puts("Erro ao abrir pipes");
        exit(-1);
    }

    if (fork() != 0) {
        wait(&status);
        close(fd[1]);
        read(fd[0], dados, strlen(text) * sizeof(char));
        printf("Resultado = %s\n", dados);
    } else {
        close(fd[0]);
        write(fd[1], text, strlen(text) * sizeof(char));
        exit(0);
    }
    return 0;
}

