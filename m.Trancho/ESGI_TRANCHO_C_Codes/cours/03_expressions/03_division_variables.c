/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int first = 1;
	int second = 2;
	float resultat;

	resultat = first / second;

	printf("%d / %d = %g\n", first, second, resultat);
	exit(EXIT_SUCCESS);
}