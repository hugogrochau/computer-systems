#include <sys/shm.h>
#include <stdio.h>

#define SHARED_KEY 8752
#define MSG_SIZE 256

int main(void) {
    int shared_id;
    char *msg;        
    shared_id = shmget(SHARED_KEY, sizeof(char) * MSG_SIZE, 0);

    msg = (char *) shmat(shared_id, NULL, 0);

    puts(msg);

    shmdt(msg);
    shmctl(shared_id, IPC_RMID,0);
    return 0;
}
