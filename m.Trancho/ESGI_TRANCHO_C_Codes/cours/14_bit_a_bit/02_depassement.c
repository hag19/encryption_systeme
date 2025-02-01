/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned long x;
	x = (1 << 42);
	printf("%lu, le bit 42 n'existe pas ? On m'a menti !\n", x);
	x = ((unsigned long)1 << 42);
	printf("%lu, ouf, rassuré !\n", x);
	exit(EXIT_SUCCESS);
}