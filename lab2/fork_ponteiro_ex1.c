#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int id,
        var = 1,
        *ptr = &var,
        status;

    if ((id = fork()) < 0) {
        puts("Erro na criação do novo processo\n");
        exit(-2);
    } else if (id == 0) {
        wait(&status);
        *ptr = 2;
        printf("Valor dentro do filho (pid=%d) - %p:%d\n", getpid(), ptr, *ptr);
    } else {
        printf("Valor dentro do pai   (pid=%d) - %p:%d\n", getpid(), ptr, *ptr);
        wait(&status);
        printf("Valor no final do pai (pid=%d) - %p:%d\n", getpid(), ptr, *ptr);
    }
    return 0;
}

/* Não ocorreu segmentation fault porque mesmo
 * sendo processos diferentes, uma copia da
 * memoria virtual é criada para o filho.
 *
 * Se o filho modificar o dado até atráves do
 * ponteiro, o pai não consiguirá ver essa
 * mudança */
