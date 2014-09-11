#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>

#define SHARED_KEY 8752
#define MSG_SIZE 256

int main(void) {
    int shared_id;
    char *msg;        
    shared_id = shmget(SHARED_KEY, sizeof(char) * MSG_SIZE,
                       IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    msg = (char *) shmat(shared_id, NULL, 0);

    fgets(msg, MSG_SIZE, stdin);

    shmdt(msg);
    return 0;
}
