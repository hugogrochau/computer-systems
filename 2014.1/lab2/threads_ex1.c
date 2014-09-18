#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *contCrescente(void *threadId) {
    int i;
    for (i = 1; i <= 20; i++) { 
        printf("Crescendo... N=%.02d\n", i);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *contDecrescente(void *threadId) {
    int i;
    for (i = 20; i >= 1; i--) { 
        printf("Diminuindo... N=%.02d\n", i);
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
