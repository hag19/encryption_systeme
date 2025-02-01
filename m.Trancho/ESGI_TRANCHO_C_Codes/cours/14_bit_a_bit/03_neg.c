/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 42;
	printf("%d + %d = %d\n", i, ~i + 1, i + ~i + 1);
	exit(EXIT_SUCCESS);
}