#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int N = 1;

void *contCrescente(void *threadId) {
    while (1) {
        N++;
        printf("Crescendo... N=%.02d\n", N);
        sleep(1);
    }
}

void *contDecrescente(void *threadId) {
    while (1) { 
        N--;
        printf("Diminuindo... N=%.02d\n", N);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[2];

    puts("Criando thread contCrescente");
    pthread_create(threads, NULL, contCrescente, NULL);
    puts("Criando thread contDescrescente");
    pthread_create(threads, NULL, contDecrescente, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    return 0;
}
