/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	long big = 5000000000000;
	printf("big est un entier : %d\n", big);
	printf("oups, big porte bien son nom : %ld\n", big);
	exit(EXIT_SUCCESS);
}