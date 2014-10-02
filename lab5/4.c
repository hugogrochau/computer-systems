#include <stdio.h>

int main(void) {
	char c;
	while ((c = fgetc(stdin)) != EOF)
		fputc(c, stdout);
	return 0;
}

