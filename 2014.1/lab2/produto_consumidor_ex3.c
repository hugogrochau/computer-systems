#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_FILA 8


int fila[MAX_FILA];
int topo = 0; 

pthread_mutex_t fila_mutex;
pthread_cond_t fila_threshold;


void FILA_push(int dado) {
    int i;
    
    for (i = topo; i > 0; i--)
        fila[i] = fila[i-1];

    if (topo < MAX_FILA)
        ++topo;

    fila[0] = dado;
}

int FILA_pop() {
    if (topo <= 0) return -1;
    return fila[--topo];
}

void FILA_print() {
    int i;
    printf("Topo = %d\n", topo);
    printf("[");
    for (i = 0; i < topo; i++)
        printf(" %.02d ", fila[i]);
    for (i = topo; i < MAX_FILA; i++)
        printf(" ## ");
    puts("]\n");
}

void *produtor(void *threadId) {
    int produto;

    for (produto = 1; produto <= 64; produto++) {
        pthread_mutex_lock(&fila_mutex);
        if (topo >= MAX_FILA) {
            printf("Sem espaco para produzir, produtor parou\n\n");
            pthread_cond_wait(&fila_threshold, &fila_mutex);
        }
        FILA_push(produto);
        printf("Produzindo produto %.02d\n", produto);
        FILA_print();
        pthread_mutex_unlock(&fila_mutex);

        sleep(1);
    }
    printf("Nao existem mais produtos a serem produzidos\n\n");
    pthread_exit(NULL);
}

void *consumidor(void *threadId) {
    int i;

    for (i = 0; i < 64; i++) {
        pthread_mutex_lock(&fila_mutex);
        printf("Consumindo produto %.02d\n", FILA_pop());
        FILA_print();
        pthread_cond_signal(&fila_threshold);
        pthread_mutex_unlock(&fila_mutex);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[2];
    pthread_mutex_init(&fila_mutex, NULL);
    pthread_cond_init(&fila_threshold, NULL);

    puts("Criando thread produtor\n");
    pthread_create(threads, NULL, produtor, NULL);
    puts("Criando thread consumidor\n");
    pthread_create(threads, NULL, consumidor, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
   
    printf("Todos produtos foram consumidos\n");
    pthread_mutex_destroy(&fila_mutex);
    pthread_cond_destroy(&fila_threshold);
    return 0;
}
