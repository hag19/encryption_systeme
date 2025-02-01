/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned long x;
	unsigned int nombre = 1;
	x = ~(nombre << 2);
	printf("%lu, Il y a un soucis ?\n", x);
	x = ~((unsigned long)nombre << 2);
	printf("%lu, Effectivement, c'est un peu plus long en fait !\n", x);
	exit(EXIT_SUCCESS);
}