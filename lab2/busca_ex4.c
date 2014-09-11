#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SHARED_KEY 12345 
#define ARRAY_SIZE 100
#define RANGE 10

int main(int argc, char **argv) {
    int status,
        *array,
        shared_id_array,
        i,j,
        key;

    pid_t pid;

    srand(time(NULL));

    if (argc < 2) {
        printf("Sintaxe: %s <key>\n", argv[0]);
        return 1;
    }

    key = atoi(argv[1]);

    shared_id_array = shmget(SHARED_KEY, sizeof(int) * ARRAY_SIZE,
                             IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    array = (int *) shmat(shared_id_array, NULL, 0);
    
    puts("Vetor gerado aleatóriamente:");
    for (i = 0; i < ARRAY_SIZE; i++) { 
        if (i % 10 == 0)
            putchar('\n');
        array[i] = (rand() % ARRAY_SIZE) + 1;
        printf("%.03d", array[i]);
        if (i != ARRAY_SIZE-1)
            putchar(',');
    }
    puts("\n");
    puts("========================================\n");
    for (i = 0; i < ARRAY_SIZE/RANGE; i++) {
        if ((pid = fork()) < 0) {
            puts("Erro na criação do novo processo");
            exit(-2);
        } else if (pid == 0) { // filho
            for (j = 0; j < RANGE; j++) {
                if (array[i*RANGE+j] == key) {
                    printf("Chave %d encontrada na posição %d\n", key, i*RANGE+j+1);
                    exit(0);
                }
            }
            exit(0);
        }
        wait(&status);
    }

    shmdt(array);
    shmctl(shared_id_array, IPC_RMID, 0);
    return 0;
}
