#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int status;
    int var = 1;

    if (fork() != 0) {
        wait(&status);
        printf("meu PID = %d\n", (int) getpid());
        printf("Resultado = %d\n", var);
    } else {
        printf("meu PID = %d\n", (int) getpid());
        var++;
        exit(0);
    }
    return 0;
}

/* O que você observa?
 * Observa-se que o var impresso pelo filho continua
 * sendo o valor original (1) pois o filho é um novo
 * processo que não mantem os mesmos variaveis do 
 * pai
 *
*/
