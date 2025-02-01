/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 42, b = 1337;
	
	printf("a = %d, b = %d\n", a, b);

	a ^= b; /* a ^ b */

	b ^= a; /* b ^ a ^ b = a */

	a ^= b; /* a ^ b ^ a = b */
	
	printf("a = %d, b = %d\n", a, b);
	
	exit(EXIT_SUCCESS);
}