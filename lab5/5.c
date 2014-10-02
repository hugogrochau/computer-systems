#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int status;
    int fd[2];

    if (pipe(fd) < 0) {
        puts("Erro ao abrir pipes");
        exit(-1);
    }

    if (fork() != 0) { // pai
        wait(&status);
        close(0); // fecha stdin
        dup(fd[0]); // bota fd[0] como stdin
        close(fd[1]); // fecha fd[1] (saida)
        execlp("grep", "grep", "4", NULL); // executa grep com fd[0] como stdin
    } else {
    	close(1); // fecha stdout
    	dup(fd[1]); // bota fd[1] como stdout
        close(fd[0]); // fecha fd[0] (entrada)
        execlp("ls", "ls", NULL); // executa tree com f[1] como stdout
        exit(0);
    }
    return 0;
}

