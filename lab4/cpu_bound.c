#include <stdio.h>
#include <math.h>

int main (void) {
	int result;
	srand(time(NULL));
	while (1) {
 		result = rand()/2 * rand()/5;
 		result = sqrt(result);
 		result = pow(result, 1.5);
 		printf("Result: %d\n", result);
	}
	return 0;
}