#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main (void) { 
	pid_t pid;

	if ((pid = fork()) < 0) {
		fprintf(stderr, "Erro a criar filho\n");
		exit(-1);
	}

	if (pid == 0)  { // filho
		execl("/bin/echo", "/bin/echo", "Codigo deste programa:", NULL);
	} else { // pai
		execl("/bin/cat", "/bin/cat", "exec.c", NULL);
	}
	return 0;
}
