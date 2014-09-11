#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SHARED_KEY 12345 

void print_matrix(int *matrix) {
    int i;
    for (i = 0; i < 9; i++) {
        if (i % 3 == 0)
            putchar('\n');
        printf(" %.02d ", matrix[i]);
    }
    puts("\n");
}

int main(void) {
    int shared_id_matrix1,
        shared_id_matrix2,
        shared_id_matrix3,
        *matrix1,
        *matrix2,
        *matrix3,
        x, y, i,
        status;

    pid_t pid;

    shared_id_matrix1 = shmget(SHARED_KEY, sizeof(int) * 3 * 3,
                               IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    shared_id_matrix2 = shmget(SHARED_KEY+1, sizeof(int) * 3 * 3,
                               IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    shared_id_matrix3 = shmget(SHARED_KEY+2, sizeof(int) * 3 * 3,
                               IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    matrix1 = (int *) shmat(shared_id_matrix1, NULL, 0);
    matrix2 = (int *) shmat(shared_id_matrix2, NULL, 0);
    matrix3 = (int *) shmat(shared_id_matrix3, NULL, 0);

    for (i = 0; i < 18; i++) {
        if (i < 9)
            *(matrix1+i) = i;
        else
            *(matrix2+i-9) = i;
    }

    puts("Matrix 1:");
    print_matrix(matrix1);
    puts("Matrix 2:");
    print_matrix(matrix2);


    for (x = 0; x < 3; x++) {
        if ((pid = fork()) < 0) {
            puts("Erro na criação do novo processo");
            exit(-2);
        } else if (pid == 0) { // filho
            for (y = 0; y < 3; y++)
                matrix3[x*3 + y] = matrix1[x*3 + y] + matrix2[x*3 + y];
            exit(0);
        }
        wait(&status);
    }

    puts("Matrix 3:");
    print_matrix(matrix3);

    shmdt(matrix1);
    shmdt(matrix2);
    shmdt(matrix3);

    shmctl(shared_id_matrix1, IPC_RMID, 0);
    shmctl(shared_id_matrix2, IPC_RMID, 0);
    shmctl(shared_id_matrix3, IPC_RMID, 0);

    return 0;
}
